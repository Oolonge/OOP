#include "elevators.h"

Elevators::Elevators(QVBoxLayout* layout_hall, QVBoxLayout* layout1, QVBoxLayout* layout2):
    controller(layout_hall), el1(layout1), el2(layout2)
{
    QObject::connect(&el1, SIGNAL(arrived(uint)), &controller, SLOT(arrive(uint)));
    QObject::connect(&el2, SIGNAL(arrived(uint)), &controller, SLOT(arrive(uint)));

    QObject::connect(&controller, SIGNAL(request_floor_el1()), &el1, SLOT(get_floor()));
    QObject::connect(&controller, SIGNAL(request_floor_el2()), &el2, SLOT(get_floor()));

    QObject::connect(&controller, SIGNAL(request_direction_el1()), &el1, SLOT(get_direction()));
    QObject::connect(&controller, SIGNAL(request_direction_el2()), &el2, SLOT(get_direction()));

    QObject::connect(&controller, SIGNAL(hallButtonProcessingRequested_el1(uint)), &el1, SLOT(hallButtonProcessing(uint)));
    QObject::connect(&controller, SIGNAL(hallButtonProcessingRequested_el2(uint)), &el2, SLOT(hallButtonProcessing(uint)));
}
