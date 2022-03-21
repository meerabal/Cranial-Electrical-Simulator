#ifndef SESSION_H
#define SESSION_H
using namespace std;
#include <string>
#include <vector>

// This is the header file for Session class
class Session
{
public:
    Session(string n="None", float f=0.5);      // default ctor
    ~Session();                                 // dtor

    string getName();
    float getFreq();

    void setName(string n);
    void setFreq(float f);

private:
    string name;
    float freq;

};
#endif // SESSION_H
