#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "cabin.h"
#include "controller.h"
#include "definitions.h"

class Elevator: public QObject
{
    Q_OBJECT
public:
    Elevator(QVBoxLayout* layout);

signals:
    unsigned int floor_requested(); //запрос этажа кабины
    Controller::direction_t direction_requested(); //запрос направления кабины
    void hallButtonProcessingRequested(uint); // запрос на обработку кнопки на этаже, uint - этаж. порождается контрллером холла
    void arrived(uint);

public slots:
    // используются для расчёта, какому лифту передать новый запрос в холле
    unsigned int get_floor() { return emit floor_requested(); };
    Controller::direction_t get_direction() { return emit direction_requested(); }
    void hallButtonProcessing(unsigned floor) { emit hallButtonProcessingRequested(floor); }

    // смена стиля кнопки
    void doorsStartedOpening();
    void doorsStartedClosing();
    void doorsFinishedClosing();
    void doorsFinishedOpening();

private:
    Cabin cabin;
    Controller controller;
};

#endif // ELEVATOR_H
