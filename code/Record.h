#ifndef RECORD_H
#define RECORD_H
using namespace std;
#include <string>
#include <vector>

#include "Session.h"

// This is the header file for Record class
class Record
{
public:
    Record(int dur=0, int i=0, Session *s=NULL);    // default ctor
    ~Record();                                      // dtor

    void incrementIntensity();                      // increments intensity by 1
    void decrementIntensity();                      // decrements intensity by 1

    int getDuration();
    int getIntensity();
    Session* getSession();
    QString getRecordString();

    void setDuration(int dur);
    void setIntensity(int i);
    void setSession(Session* s);

private:
    int duration;
    int intensity;          // can have values 0 to 7
    Session *session;

};
#endif // RECORD_H
