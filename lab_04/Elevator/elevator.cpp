#include "elevator.h"

Elevator::Elevator(QVBoxLayout* layout): controller(layout)
{
    QObject::connect(&cabin, SIGNAL(finished()), &controller, SLOT(chooseNewDestination()));
    QObject::connect(&controller, SIGNAL(moveCabin()), &cabin, SLOT(move()));
    QObject::connect(&controller, SIGNAL(stopCabin()), &cabin, SLOT(stop()));

    QObject::connect(this, SIGNAL(floor_requested()), &controller, SLOT(get_floor()));
    QObject::connect(this, SIGNAL(direction_requested()), &controller, SLOT(get_direction()));
    QObject::connect(this, SIGNAL(hallButtonProcessingRequested(uint)), &controller, SLOT(processNewDestination(uint)));

    // порождаем его здесь, чтобы пробросить его в hall_buttons
    QObject::connect(&controller, SIGNAL(arrived(uint)), this, SIGNAL(arrived(uint)));

    // используются для обновления styleSheet'ов кнопок
    QObject::connect(&cabin, SIGNAL(openDoors()), this, SLOT(doorsStartedOpening()));
    QObject::connect(&cabin, SIGNAL(closeDoors()), this, SLOT(doorsStartedClosing()));
    QObject::connect(&cabin, SIGNAL(finished()), this, SLOT(doorsFinishedClosing()));
    QObject::connect(&cabin, SIGNAL(doorsFinishedOpening()), this, SLOT(doorsFinishedOpening()));
}

void Elevator::doorsStartedOpening()
{
    controller.button_list[controller.curr_floor]->setStyleSheet(STYLE_OPENING);
}

void Elevator::doorsStartedClosing()
{
    controller.button_list[controller.curr_floor]->setStyleSheet(STYLE_CLOSING);
}

void Elevator::doorsFinishedClosing()
{
    controller.button_list[controller.curr_floor]->setStyleSheet(STYLE_ELEVATOR);
}

void Elevator::doorsFinishedOpening()
{
    controller.button_list[controller.curr_floor]->setStyleSheet(STYLE_OPEN);
}
