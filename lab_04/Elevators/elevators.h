#ifndef ELEVATORS_H
#define ELEVATORS_H

#include <QObject>
#include "hall_buttons_controller.h"
#include "elevator.h"

class Elevators : public QObject
{
    Q_OBJECT
public:
    Elevators(QVBoxLayout* layout_hall, QVBoxLayout* layout1, QVBoxLayout* layout2);

private:
    HallButtonsController controller;
    Elevator el1;
    Elevator el2;
};

#endif // ELEVATORS_H
