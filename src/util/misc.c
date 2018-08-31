
#include <error.h>

/* needed for gcc */
abort(){
    PANIC("abort");
}


unsigned int
djb2_hash(const unsigned char *src, int len){
    unsigned long hash = 5381;

    for( ; len; len--)
        hash = (33 * hash) ^ (*src++);

    return hash;
}

unsigned int
fnv1a_hash(const unsigned char *src, int len){
    unsigned long hash = 2166136261;
    int c;

    for( ; len; len--){
        hash ^= *src++;
        hash *= 16777619;
    }

    return hash;
}

unsigned long long
fnv64_hash(const unsigned char *src, int len){
    unsigned long long hash = 14695981039346656037ULL;
    int c;

    for( ; len; len--){
        hash ^= *src++;
        hash *= 1099511628211ULL;
    }

    return hash;
}

