#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>
#include <stdlib.h>



#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

static inline void 
die(const char* text) {
    fprintf(stderr, "%s", text);
    exit(EXIT_FAILURE);
}

#ifdef __cplusplus
}
#endif //__cplusplus
#endif /* ERRORS_H */
