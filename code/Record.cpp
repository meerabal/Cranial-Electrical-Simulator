#include <iostream>
using namespace std;
#include <string>

#include "Record.h"

// This is the Record class - contains a Session pointer, intensity, duration
Record::Record(int dur, int i, Session *s)
    : duration(dur),
      intensity(i),
      session(s)
{ }

Record::~Record()
{
    delete session;
}

void Record::incrementIntensity() {
    if(intensity+1 < 8) {
        intensity++;
    }
}

void Record::decrementIntensity() {
    if(intensity-1 >= 0) {
        intensity--;
    }
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

QString Record::getRecordString() {
    QString str = "Session: NONE,\n";
    if(session != NULL) {
        str = session->getSessionString();
    }
    str = str + "Duration: " + QString::number(duration) + " min,\n"
            + "Intensity: " + QString::number(intensity) + " V\n";
    return str;
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
