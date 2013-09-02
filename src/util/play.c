/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Apr-09 19:58 (EDT)
  Function: play music
*/


#include <math.h>
#include <stdint.h>
#include <proc.h>
#include <userint.h>

extern void beep(int freq, int vol, int duration);

// sort-of:
//   http://en.wikipedia.org/wiki/Music_Macro_Language#Classical_MML_2
void
play(int vol, const char *tune){
    short freq=0, bpm=120, dur=4, pdur=4;
    int8_t octave=4, poctave=4, sharp=0, ratio=8, barct=0, dots=0;
    const char *bar=0;

    // note: [A-GZ][+-#_~.<>][0-8]

    while( *tune ){
        switch(tolower(*tune)){
        case ' ':               break;	// ignored
        case '+': octave ++;    break;
        case '-': octave --;    break;
        case '>': ratio += 4;   break;	// legato
        case '<': ratio /= 2;   break;	// staccato
        case '#': sharp = 1;    break;
        case '_': sharp = -1;   break;
        case '~': dur *=  3;    break;	// triplet
        case '.': dots ++;      break;
        case '0': dur  =  1;    break;
        case '1': dur  =  2;    break;
        case '2': dur  =  4;    break;
        case '3': dur  =  8;    break;
        case '4': dur  = 16;    break;
        case '5': dur  = 32;    break;
        case '6': dur  = 64;    break;
        case '7': dur  = 128;   break;
        case '8': dur  = 256;   break;
        case 'c': freq = 4186;  break;
        case 'd': freq = 4699;  break;
        case 'e': freq = 5274;  break;
        case 'f': freq = 5588;  break;
        case 'g': freq = 6272;  break;
        case 'a': freq = 7040;  break;
        case 'b': freq = 7902;  break;

        case 'r': // rest
        case 'z':
                  freq = 0;     break;

        case 's': // synchronize
            freq = -1;
            currproc->flags |= PRF_SIGWAKES;
            tsleep( &play, -1, "play", 2000000 );
            break;

        case 'o': // change base octave - stays in effect until another O: O5
            poctave = 0;
            freq = -1;
            while( tune[1] && isdigit(tune[1]) ){
                poctave *= 10;
                poctave += tune[1] - '0';
                tune ++;
            }
            octave = poctave;
            break;

        case 'l': // change default note duration: L32
            pdur = 0;
            freq = -1;
            while( tune[1] && isdigit(tune[1]) ){
                pdur *= 10;
                pdur += tune[1] - '0';
                tune ++;
            }
            dur = pdur;
            break;

        case 't': // tempo: T120
        case '@':
            bpm  = 0;
            freq = -1;
            while( tune[1] && isdigit(tune[1]) ){
                bpm *= 10;
                bpm += tune[1] - '0';
                tune ++;
            }
            break;

        case '[':	// repeat [count ... ]
            barct = 0;
            while( tune[1] && isdigit(tune[1]) ){
                barct *= 10;
                barct += tune[1] - '0';
                tune ++;
            }
            bar = tune + 1;
            break;
        case ']':
            if( bar && --barct > 0 )
                tune = bar;
            break;

        default:
            // ignore
            break;
        }

        if( (!tune[1] || isalpha(tune[1])) && freq >= 0 ){
            // play the note
            if( octave < 0 ) octave = 0;
            if( octave > 8 ) octave = 8;

            freq >>= 8 - octave;

            if( ratio < 1 )  ratio = 1;
            if( ratio > 16 ) ratio = 16;

            if( sharp ) freq += ((long)freq * 3900L * sharp) / 65536;

            int tb   = 125000 * 120;
            short db = dur * bpm;

            if( dots ){
                tb = (tb * ((2<<dots) - 1)) >> dots;
            }
            if( freq && vol )
                beep(freq, vol, tb * ratio / db );
            else
                usleep( tb * ratio / db );

            if( ratio != 16 )
                usleep( tb * (16 - ratio) / db );

            dur    = pdur;
            octave = poctave;
            sharp  = 0;
            freq   = 0;
            ratio  = 8;
            dots   = 0;
        }

        tune++;
    }
}

#ifdef USE_CLI

DEFUN(play, "play music")
{
    int i, vol=4;

    if( argc < 2 ){
        fprintf(STDERR, "ERROR: play [-v vol] notes...\n");
        return -1;
    }

    if( argc > 3 && !strcmp(argv[1], "-v") ){
        vol = atoi( argv[2] );
        argc -= 2;
        argv += 2;
    }

    for(i=1; i<argc; i++){
        play(vol, argv[i]);
    }
    return 0;
}

#endif

