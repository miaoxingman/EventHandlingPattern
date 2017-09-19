#include <map>
#include <string>
#include "EventType.h"

std::map<int, std::string> eventTypeMap = 
{
    {01, "READ_EVENT or ACCEPT_EVENT"},
    {02, "WRITE_EVENT"},
    {04, "TIMEOUT_EVENT"},
    {010, "SIGNAL_EVENT"},
    {020, "CLOSE_EVENT"}
};

const char* getEventString(EventType et) {
    return eventTypeMap[et].c_str();
}