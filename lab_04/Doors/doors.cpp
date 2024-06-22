#include "doors.h"
#include <iostream>
using namespace std;

#define TIME_CLOSURE 3000
#define TIME_OPENING 3000
#define TIME_WAITING 2000

Doors::Doors()
{
    QObject::connect(&closure_timer, SIGNAL(timeout()), this, SLOT(close()));
    QObject::connect(&opening_timer, SIGNAL(timeout()), this, SLOT(open()));
    QObject::connect(&waiting_timer, SIGNAL(timeout()), this, SLOT(startClosing()));
}

void Doors::startClosing()
{
    if (status != OPEN)
        return;
    status = CLOSING;

    cout << "Двери закрываются..." << endl;

    closure_timer.start(TIME_CLOSURE);
    emit startClosingSignal();
}

void Doors::startOpening()
{
    if (status != CLOSED)
        return;
    status = OPENING;
    cout << "Двери открываются..." << endl;

    opening_timer.start(TIME_OPENING);
    emit startOpeningSignal();
}

void Doors::close()
{
    if (status != CLOSING)
        return;

    status = CLOSED;
    cout << "Двери закрыты." << endl;

    emit doorsClosed();
}

void Doors::open()
{
    if (status != OPENING)
        return;

    status = OPEN;
    cout << "Двери открыты." << endl;

    waiting_timer.start(TIME_WAITING);
    emit doorsOpen();
}
