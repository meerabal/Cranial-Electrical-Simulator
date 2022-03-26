#include <iostream>
using namespace std;
#include <string>

#include "Session.h"

// ctor
Session::Session(QString n, float f)
    : name(n),
      freq(f)
{ }

// dtor
Session::~Session()
{ }

QString Session::getName() {
    return name;
}

float Session::getFreq() {
    return freq;
}

QString Session::getSessionString() {
    QString str = "Session name: " + name + ",\n"
            + "Frequency: " + QString::number(freq) + ",\n";
    return str;
}

void Session::setName(QString n) {
    name = n;
}

void Session::setFreq(float f) {
    freq = f;
}
