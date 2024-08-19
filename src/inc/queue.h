/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Jun-23 12:30 (EDT)
  Function: queue

*/

#ifndef __osj5_queue_h__
#define __osj5_queue_h__

#ifndef QUEUE_TYPE
#  define QUEUE_TYPE char
#endif

struct queue {
    uint16_t head, tail, len, size;
    QUEUE_TYPE *d;
};

static void
queue_init_buf(struct queue *q, QUEUE_TYPE *d, int size){
    q->d = d;
    q->size = size;
    q->head = q->tail = q->len = 0;
}

static void
queue_init(struct queue *q, int size){
    QUEUE_TYPE *d = malloc(size * sizeof(QUEUE_TYPE));
    if( !d ){
        PANIC("cannot malloc queue");
    }
    queue_init_buf(q, d, size);
}

static int
qfull(struct queue *q){
    return ( q->len >= q->size );
}

static int
qempty(struct queue *q){
    return q->len == 0;
}

static int
qpush(struct queue *q, int c){

    if( q->len >= q->size ) return -1;

    q->d[ q->head ++ ] = c;
    q->head %= q->size;
    q->len ++;
    return 0;
}

// add one contiguous chunk
static int
qwrite(struct queue *q, const QUEUE_TYPE *src, int len){
    int e = (q->tail > q->head) ? q->tail : q->size;
    int s = e - q->head;
    if( s > len ) s = len;

    bcopy(src, q->d + q->head, s * sizeof(QUEUE_TYPE));

    q->head += s;
    if( q->head == q->size ) q->head = 0;

    q->len += s;

    return s;
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

// pop off as much as we can
static int
qread(struct queue *q, QUEUE_TYPE *dst, int maxlen){
    int n = 0;

    // first, tail to end
    int s = q->size - q->tail;
    if( s > q->len ) s = q->len;
    if( s > maxlen ) s = maxlen;

    if( !s ) return 0;

    bcopy(q->d + q->tail, dst, s * sizeof(QUEUE_TYPE));

    q->tail += s;
    if( q->tail == q->size ) q->tail = 0;
    q->len -= s;
    maxlen -= s;
    dst += s;
    n += s;

    if( q->len == 0 ){
        q->head = q->tail = 0;
        return n;
    }

    if( !maxlen ) return n;

    // then, a second chunk at front
    s = q->size - q->tail;
    if( s > q->len ) s = q->len;
    if( s > maxlen ) s = maxlen;

    bcopy(q->d + q->tail, dst, s * sizeof(QUEUE_TYPE));
    q->tail += s;
    if( q->tail == q->size ) q->tail = 0;
    q->len -= s;
    n += s;

    if( q->len == 0 ) q->head = q->tail = 0;

    return n;
}

static int
qxfer(struct queue *src, struct queue *dst){
    int r, n = 0;

    if( qempty(src) ) return n;
    if( qfull(dst)  ) return n;

    // tail .. end
    int s = src->size - src->tail;
    if( s > src->len ) s = src->len;
    r = qwrite(dst, src->d + src->tail, s);
    src->tail += r;
    if( src->tail == src->size ) src->tail = 0;
    src->len -= r;
    n += r;

    if( qempty(src) ) return n;
    if( qfull(dst)  ) return n;

    // start .. head
    s = src->size - src->tail;
    if( s > src->len ) s = src->len;
    r = qwrite(dst, src->d + src->tail, s);
    src->tail += r;
    if( src->tail == src->size ) src->tail = 0;
    src->len -= r;
    n += r;

    return n;
}


#endif /* __osj5_queue_h__ */
