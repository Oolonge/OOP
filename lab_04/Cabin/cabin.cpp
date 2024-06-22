#include "cabin.h"
#define MOVE_TIME 1500
#define STOP_DELAY 500
#include <iostream>
#include <QObject>

Cabin::Cabin()
{
    QObject::connect(this, SIGNAL(openDoors()), &doors, SLOT(startOpening()));
    QObject::connect(&move_timer, SIGNAL(timeout()), this, SLOT(become_idle()));
    QObject::connect(&doors, SIGNAL(doorsClosed()), this, SLOT(become_idle()));

    QObject::connect(&stop_delay, SIGNAL(timeout()), this, SLOT(wait()));

    QObject::connect(&doors, SIGNAL(startClosingSignal()), this, SIGNAL(closeDoors()));
    QObject::connect(&doors, SIGNAL(doorsOpen()), this, SIGNAL(doorsFinishedOpening()));
}

void Cabin::move()
{
    if (status == STOPPING || status == MOVING)
        return;

    status = MOVING;
    move_timer.start(MOVE_TIME);
}


void Cabin::stop()
{
    if (status == STOPPING || status == WAITING)
        return;
    status = STOPPING;
    move_timer.stop();

    stop_delay.start(STOP_DELAY); // задержка перед открытием дверей
}

void Cabin::wait()
{
    if (status != STOPPING)
        return;
    // std::cout << "Кабина ожидает полного закрытия дверей" << std::endl;

    status = WAITING;
    emit openDoors();
}

void Cabin::become_idle()
{
    if (status == IDLE)
        return;
    status = IDLE;
    emit finished();
}
