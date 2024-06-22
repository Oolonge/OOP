#ifndef CONTROLLER_H
#define CONTROLLER_H

#define STARTING_FLOOR 1

#include "button.h"
#include <QVBoxLayout>
#include <memory>

using namespace std;

class   Controller: public QObject
{
    Q_OBJECT
    friend class Elevator;
    using controllerStatus = enum
    {
        IDLE, REQUEST_PROCESSING, CHOOSING_DEST, UPDATING, CABIN_DIRECTION
    };

public:
    using direction_t = enum
    {
        DOWN = -1,
        UP = 1,
        HOLD = 0
    };

public:
    Controller(QVBoxLayout* layout);
    ~Controller();

signals:
    void stopCabin();
    void moveCabin();
    void arrived(uint);
    void requestProcessed();
    void destinationChosen();
    void CabinDirected();
    void floor_updated(bool);


public slots:
    void processNewDestination(unsigned int); // 2
    void directCabin(); // 4

private slots:
    void become_idle(bool is_active); // 1
    void chooseNewDestination(); // 3
    void updateFloor(); // 5

    void arrive(unsigned int);

    // нужно для контроллера холла
    unsigned int get_floor() { return curr_floor; }
    unsigned int get_direction() { return direction; }

private:
    controllerStatus status = IDLE;

    unsigned int curr_floor = STARTING_FLOOR;
    unsigned int destination_floor = STARTING_FLOOR;

    direction_t direction = HOLD;
    direction_t previous_direction = HOLD;

    vector<unique_ptr<Button>> button_list;
    vector<bool> floors_to_visit {};
    bool first_request = true;
};

#endif // CONTROLLER_H
