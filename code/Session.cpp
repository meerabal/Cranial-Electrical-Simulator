#include <iostream>
using namespace std;
#include <string>

#include "Session.h"

// ctor
Session::Session(string n, float f)
    : name(n),
      freq(f)
{ }

// dtor
Session::~Session()
{ }

string Session::getName() {
    return name;
}

float Session::getFreq() {
    return freq;
}

void Session::setName(string n) {
    name = n;
}

void Session::setFreq(float f) {
    freq = f;
}
