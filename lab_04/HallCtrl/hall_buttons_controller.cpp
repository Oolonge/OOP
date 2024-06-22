#include "hall_buttons_controller.h"
#include "definitions.h"

#include <QLabel>

HallButtonsController::HallButtonsController(QVBoxLayout* layout_hall)
{
    layout_hall->addWidget(new QLabel("Кнопки в холлах"));

    for (int i = FLOORS; i >= 0; i--)
    {
        hall_buttons.insert(hall_buttons.begin(), make_unique<Button>(i));

        layout_hall->addWidget(hall_buttons[0].get());

        QObject::connect(hall_buttons[0].get(), SIGNAL(_pressed(uint)), this, SLOT(processButtonClick(uint)));
    }
    QObject::connect(this, SIGNAL(requestProcessed()), this, SLOT(requestElevatorData()));
    QObject::connect(this, SIGNAL(elevatorDataRequested(uint,uint,direction_t,direction_t)),
                     this, SLOT(processElevatorData(uint,uint,direction_t,direction_t)));
    QObject::connect(this, SIGNAL(finished()), this, SLOT(become_idle()));
    QObject::connect(this, SIGNAL(requestSent()), this, SLOT(checkQueue()));
}

HallButtonsController::~HallButtonsController()
{
    for (auto& ptr: hall_buttons)
        ptr.release();
}

unsigned int HallButtonsController::calculate_weight(unsigned curr_floor, unsigned destination, Controller::direction_t& dir)
{
    /*
     * diff > 0 => надо вверх
     * diff < 0 => надо вниз
     * diff = 0 => никуда не надо
     */
    int diff = destination - curr_floor;
    if (diff > 0 && dir != Controller::DOWN)
        return (unsigned) diff;
    else if (diff > 0) // && dir == Controller::DOWN
        return curr_floor + destination;
    else if (dir != Controller::UP) // && diff < 0
        return -diff;
    else
        return FLOORS - curr_floor + FLOORS - destination;
}

void HallButtonsController::processButtonClick(unsigned int floor)
{
    if (status != IDLE)
    {
        requests.push(floor);
        return;
    }

    status = PROCESSING_REQUEST;

    this->floor = floor;

    emit requestProcessed();
}

void HallButtonsController::requestElevatorData()
{
    status = REQUESTING_DATA;

    unsigned floor_el1 = emit request_floor_el1(),
        floor_el2 = emit request_floor_el2();

    direction_t dir_el1 = emit request_direction_el1(),
        dir_el2 = emit request_direction_el2();

    emit elevatorDataRequested(floor_el1, floor_el2, dir_el1, dir_el2);
}

void HallButtonsController::processElevatorData(unsigned floor1, unsigned floor2,
                                                direction_t dir1, direction_t dir2)
{
    status = CHOOSING_ELEVATOR;
    unsigned w1 = calculate_weight(floor1, floor, dir1);
    unsigned w2 = calculate_weight(floor2, floor, dir2);

    if (w1 < w2)
        emit hallButtonProcessingRequested_el1(floor);
    else
        emit hallButtonProcessingRequested_el2(floor);
    emit requestSent();
}

void HallButtonsController::become_idle()
{
    if (status != CHECKING_REQUESTS)
        return;

    status = IDLE;
    emit finished();
}

void HallButtonsController::checkQueue()
{
    if (status != CHOOSING_ELEVATOR)
        return;
    status = CHECKING_REQUESTS;
    if (! requests.empty())
    {
        emit hall_buttons[requests.back()]->_pressed(requests.back());
        requests.pop();
    }
    emit finished();
}


void HallButtonsController::arrive(unsigned int floor)
{
    emit hall_buttons[floor]->_unpressed();
    hall_buttons[floor]->setStyleSheet(STYLE_INACTIVE);
    hall_buttons[floor]->update();
}
