#ifndef TOKENIZER_COMMON_PKG_H
#define TOKENIZER_COMMON_PKG_H

/* this is the size of the event queue */
#define QSIZE 100

typedef enum EventType {
    EVDIGIT,
    EVDOT,
    EVWHITESPACE,
    EVENDOFSTRING
} EventType;

typedef struct {
    EventType eType;
    union eventData {
        char c;
    } ed;
} Event;

typedef enum TSTATETYPE {
    NULL_STATE,
    NONUMBER_STATE,
    GOTNUMBER_STATE
} TSTATETYPE;

typedef enum TSUBSTATETYPE {
    NULL_SSTATE,
    PROCESSINGWHOLEPART_SSTATE,
    PROCESSINGFRACTIONALPART_SSTATE
} TSUBSTATETYPE;

/* helper function returns the digit */
/* held by a char */
int digit(char c) {
    return c-'0';
}

#endif
