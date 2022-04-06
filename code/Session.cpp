#include <iostream>
using namespace std;
#include <string>

#include "Session.h"

// This is session class - contains session name and frequency
Session::Session(QString n, float f)
    : name(n),
      freq(f)
{ }

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
            + "Frequency: " + QString::number(freq) + " Hz,\n";
    return str;
}

void Session::setName(QString n) {
    name = n;
}

void Session::setFreq(float f) {
    freq = f;
}
