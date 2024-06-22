#include "controller.h"
#include "definitions.h"
#include <QLabel>
#include <iostream>

Controller::Controller(QVBoxLayout* layout)
{
    layout->addWidget(new QLabel("Кнопки лифта"));

    for (int i = FLOORS; i >= 0; i--)
    {
        button_list.insert(button_list.begin(), make_unique<Button>(i));

        layout->addWidget(button_list[0].get());
        floors_to_visit.push_back(false);

        QObject::connect(button_list[0].get(), SIGNAL(_pressed(uint)), this, SLOT(processNewDestination(uint)));
    }

    button_list[STARTING_FLOOR]->setStyleSheet(STYLE_ELEVATOR);

    QObject::connect(this, SIGNAL(requestProcessed()), this, SLOT(chooseNewDestination()));
    QObject::connect(this, SIGNAL(destinationChosen()), this, SLOT(directCabin()));
    QObject::connect(this, SIGNAL(CabinDirected()), this, SLOT(updateFloor()));
    QObject::connect(this, SIGNAL(floor_updated(bool)), this, SLOT(become_idle(bool)));

    QObject::connect(this, SIGNAL(arrived(uint)), this, SLOT(arrive(uint)));
}

Controller::~Controller()
{
    for (auto& ptr: button_list)
        ptr.release();
}

void Controller::processNewDestination(unsigned int new_floor)
{
    if (new_floor > FLOORS)
        return;

    status = REQUEST_PROCESSING;

    floors_to_visit[new_floor] = true;

    if (first_request == false)
    {
        emit floor_updated(false);
        return;
    }
    emit requestProcessed();
}

void Controller::directCabin()
{
    status = CABIN_DIRECTION;

    if (direction == HOLD)
    {
        emit arrived(curr_floor);
    }
    else
        emit moveCabin();

    emit CabinDirected();
}

void Controller::chooseNewDestination()
{
    status = CHOOSING_DEST;

    direction_t direct = direction;
    if (direct == HOLD && previous_direction == HOLD)
        direct = UP;
    else if (direct == HOLD)
        direct = previous_direction;

    previous_direction = direction;
    for (size_t k = 0; k < 2; k++)
    {
        for (int i = curr_floor; i >= 0 && i <= FLOORS; i += direct)
            if (floors_to_visit[i])
            {
                destination_floor = i;
                direction = (destination_floor == curr_floor) ? HOLD : direct;

                emit destinationChosen(); // ещё есть этажи для посещения
                return;
            }
        if (k == 0)
            direct = (direct == UP) ? DOWN : UP;
    }
    direction = HOLD;
    emit floor_updated(false);
}

void Controller::updateFloor()
{
    status = UPDATING;

    if (! first_request)
    {
        curr_floor += direction;
        button_list[curr_floor]->setStyleSheet(STYLE_ELEVATOR);
        button_list[curr_floor - direction]->setStyleSheet(STYLE_INACTIVE);
        cout << "Лифт на этаже №" << curr_floor << endl;
    }


    first_request = false;
    emit floor_updated(true);
}

void Controller::arrive(unsigned int floor)
{
    if (status == IDLE)
        return;

    cout << "Лифт остановился на этаже №" << floor << endl;

    emit button_list[floor]->_unpressed();
    floors_to_visit[floor] = false;

    emit stopCabin();
}

void Controller::become_idle(bool first_request_flag)
{
    status = IDLE;

    // if all false => first_req = ture, else = false
    if (first_request_flag == false)
        first_request = std::all_of(floors_to_visit.begin(), floors_to_visit.end(),
                                    [](bool x) { return !x; });
}
