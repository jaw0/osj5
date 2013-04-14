/*
  Play Music
  I think Andy wrote most of this, circa 1994
*/

#include <proc.h>
#include <gpio.h>
#include <pwm.h>


#define frequency(note,octave) ((u_short)(note>>(octave+22)))
#define REST    0
#define N_C     1097337155L
#define N_CS    1162588217L
#define N_DF    N_CS
#define N_D     1231719310L
#define N_DS    1304961152L
#define N_EF    N_DS
#define N_E     1382558180L
#define N_F     1464769368L
#define N_FS    1551869087L
#define N_GF    N_FS
#define N_G     1644148025L
#define N_GS    1741914154L
#define N_AF    N_GS
#define N_A     1845493759L
#define N_AS    1955232529L
#define N_BF    N_AS
#define N_B     2071496705L
#define O_C0    2
#define O_C1    1
#define O_C2    0
#define O_C3    -1
#define O_C4    -2
#define O_C5    -3
#define O_C6    -4
#define O_C7    -5

#define ONE_MINUTE  60000UL       /* 60 seconds        */

#define duration(bbm,note) ((u_short)((((ONE_MINUTE<<2)/(u_long)(bbm))*(u_long)(note))/(u_long)WHOLE))
#define WHOLE           (16*3)                  /* Whole note  ( 1 / smallest note ) */
#define HALF            (WHOLE/2)               /* Half note      */
#define QUARTER         (WHOLE/4)               /* Quarter note   */
#define EIGHTH          (WHOLE/8)               /* Eighth note    */
#define SIXTEENTH       (WHOLE/16)              /* Sixteenth note */
#define T_QUARTER       (QUARTER/3)             /* Triplets - Quarter   */
#define T_EIGHTH        (EIGHTH/3)              /*            Eighth    */
#define T_SIXTEENTH     (SIXTEENTH/3)   /*            Sixteenth */

#define rest(dur) {REST,duration(BBM,(dur))}
#define p1(note,octave,dur) {frequency(note,octave),duration(BBM,(dur))}
#define p2(note,octave,dur1,dur2) p1(note,octave,(dur1)-(dur2)),rest((dur2))

#define TUNE_END {0,0}

typedef struct {
        u_short frequency;
        u_short duration;
} Tune;

#define BBM 66          /* Beats per minute  */

static const Tune chariotsOfFire[] = {
        p2(N_C,O_C4,EIGHTH,T_SIXTEENTH),
        p1(N_G,O_C4,T_EIGHTH),
        p1(N_A,O_C4,T_EIGHTH),
        p1(N_B,O_C4,T_EIGHTH),
        p2(N_G,O_C4,QUARTER,SIXTEENTH),
        p2(N_E,O_C4,QUARTER,T_EIGHTH),
        p2(N_E,O_C4,EIGHTH,T_EIGHTH),
        p2(N_C,O_C4,EIGHTH,T_SIXTEENTH),
        p1(N_G,O_C4,T_EIGHTH),
        p1(N_A,O_C4,T_EIGHTH),
        p1(N_B,O_C4,T_EIGHTH),
        p1(N_G,O_C4,QUARTER),
        p1(N_G,O_C4,QUARTER),
        p2(N_G,O_C4,EIGHTH,T_EIGHTH),
        p2(N_C,O_C4,EIGHTH,T_SIXTEENTH),
        p1(N_G,O_C4,T_EIGHTH),
        p1(N_A,O_C4,T_EIGHTH),
        p1(N_B,O_C4,T_EIGHTH),
        p2(N_G,O_C4,QUARTER,SIXTEENTH),
        p1(N_E,O_C4,QUARTER),
        p2(N_E,O_C4,EIGHTH,T_EIGHTH),
        p1(N_E,O_C4,EIGHTH),
        p1(N_F,O_C4,T_EIGHTH),
        p1(N_E,O_C4,T_EIGHTH),
        p1(N_D,O_C4,T_EIGHTH),
        p1(N_C,O_C4,HALF),
        p2(N_C,O_C4,QUARTER,EIGHTH),
        p1(N_C,O_C5,T_EIGHTH),
        p1(N_B,O_C4,T_EIGHTH),
        p1(N_A,O_C4,T_EIGHTH),
        p1(N_B,O_C4,EIGHTH),
        p2(N_B,O_C4,SIXTEENTH,T_SIXTEENTH),
        p1(N_G,O_C4,SIXTEENTH),
        p1(N_A,O_C4,EIGHTH),
        p2(N_A,O_C4,SIXTEENTH,T_SIXTEENTH),
        p1(N_F,O_C4,SIXTEENTH),
        p2(N_G,O_C4,EIGHTH,T_SIXTEENTH),
        p1(N_C,O_C5,T_EIGHTH),
        p1(N_B,O_C4,T_EIGHTH),
        p1(N_A,O_C4,T_EIGHTH),
        p1(N_B,O_C4,QUARTER),
        p2(N_C,O_C5,EIGHTH,T_SIXTEENTH),
        p1(N_C,O_C5,T_EIGHTH),
        p1(N_B,O_C4,T_EIGHTH),
        p1(N_A,O_C4,T_EIGHTH),
        p1(N_B,O_C4,EIGHTH),
        p2(N_B,O_C4,SIXTEENTH,T_SIXTEENTH),
        p1(N_G,O_C4,SIXTEENTH),
        p1(N_A,O_C4,EIGHTH),
        p2(N_A,O_C4,SIXTEENTH,T_SIXTEENTH),
        p1(N_F,O_C4,SIXTEENTH),
        p1(N_G,O_C4,EIGHTH),
        p2(N_G,O_C4,SIXTEENTH,T_SIXTEENTH),
        p2(N_E,O_C4,SIXTEENTH,T_SIXTEENTH),
        p1(N_F,O_C4,T_EIGHTH),
        p1(N_E,O_C4,T_EIGHTH),
        p1(N_D,O_C4,T_EIGHTH),
        p2(N_C,O_C4,HALF,EIGHTH),
        TUNE_END
};

extern int curr_song;

static inline void
beep(int freq, int vol, int dur){
    freq_set(TIMER_3_3, freq);
    pwm_set(TIMER_3_3,  vol);
    usleep(dur);
    pwm_set(TIMER_3_3,  0);
}

void
sing_song(void){
    int cn = 0;

    printf("cof: %x\n", chariotsOfFire);

    while(1){
        if( ! curr_song ){
            usleep( 100000 );
            continue;
        }

        cn = 0;
        while(1){
            if( ! curr_song ) break;
            if( ! chariotsOfFire[cn].duration ) break;

            printf("%d: freq %d, dur %d\n", cn, chariotsOfFire[cn].frequency, chariotsOfFire[cn].duration );
            beep( chariotsOfFire[cn].frequency, 8, chariotsOfFire[cn].duration * 1000 );
            cn ++;
        }
    }
}

