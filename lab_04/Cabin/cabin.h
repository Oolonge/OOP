#ifndef CABIN_H
#define CABIN_H
#include "doors.h"

#include <QTimer>
#include <QObject>

class Cabin: public QObject
{
    Q_OBJECT

    using cabinStatus = enum
    {
        MOVING, STOPPING, IDLE, WAITING
    };

public:
    explicit Cabin();

signals:
    void finished();
    void openDoors();
    void closeDoors();
    void doorsFinishedOpening();

public slots:
    void move();
    void stop();
    void wait();
    void become_idle();

private:
    cabinStatus status = IDLE;
    Doors doors;
    QTimer move_timer;
    QTimer stop_delay;
};

#endif // CABIN_H
