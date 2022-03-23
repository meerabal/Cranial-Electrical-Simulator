#include <iostream>
using namespace std;
#include <string>

#include "Record.h"

// ctor
Record::Record(int dur, int i, Session *s)
    : duration(dur),
      intensity(i),
      session(s)
{ }

// dtor
Record::~Record()
{
    delete session;
}

int Record::getDuration() {
    return duration;
}

int Record::getIntensity() {
    return intensity;
}

Session* Record::getSession() {
    return session;
}

void Record::setDuration(int dur) {
    duration = dur;
}

void Record::setIntensity(int i) {
    intensity = i;
}

void Record::setSession(Session* s) {
    session = s;
}
