/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Jun-23 12:30 (EDT)
  Function: queue

*/

#ifndef __osj5_queue_h__
#define __osj5_queue_h__

struct queue {
    uint16_t head, tail, len, size;
    char *d;
};

static void
queue_init(struct queue *q, int size){
    q->d = malloc(size);
    if( !q->d ){
        PANIC("cannot malloc queue");
    }
    q->size = size;
    q->head = q->tail = q->len = 0;
}


static int
qpush(struct queue *q, int c){

    if( q->len >= q->size ) return -1;

    q->d[ q->head ++ ] = c;
    q->head %= q->size;
    q->len ++;
    return 0;
}

static int
qpop(struct queue *q){

    if( q->len <= 0 ) return -1;

    int c = q->d[ q->tail ++ ];
    q->tail %= q->size;
    q->len --;

    if( q->len == 0 ) q->head = q->tail = 0;

    return c;
}


#endif /* __osj5_queue_h__ */
