#ifndef __EVENT_TYPE_H__
#define __EVENT_TYPE_H__

typedef unsigned int EventType;

enum {
    READ_EVENT      = 01,
    ACCEPT_EVENT    = 01, 
    WRITE_EVENT     = 02,
    TIMEOUT_EVENT   = 04,
    SIGNAL_EVENT    = 010,
    CLOSE_EVENT     = 020
};

const char* getEventString(EventType et);

#endif //__EVENT_TYPE_H__