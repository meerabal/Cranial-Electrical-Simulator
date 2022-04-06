#ifndef SESSION_H
#define SESSION_H
using namespace std;
#include <string>
#include <vector>
#include "QString"

// This is the header file for Session class
class Session
{
public:
    Session(QString n="None", float f=0.5);      // default ctor
    ~Session();                                  // dtor

    QString getName();
    float getFreq();
    QString getSessionString();                 // getter for a string containing session name and frequency details

    void setName(QString n);
    void setFreq(float f);

private:
    QString name;
    float freq;

};
#endif // SESSION_H
