#ifndef HALL_BUTTONS_CONTROLLER_H
#define HALL_BUTTONS_CONTROLLER_H
#include "elevator.h"

#include <queue>

class HallButtonsController: public QObject
{
    Q_OBJECT

    using direction_t = Controller::direction_t;

    using controllerStatus = enum
    {
        IDLE,
        PROCESSING_REQUEST, // обработка запроса
        REQUESTING_DATA, // состояние запроса данных у каждого из лифтов
        CHOOSING_ELEVATOR, // выбор лифта
        CHECKING_REQUESTS // проверка запросов из очереди
    };

public:
    HallButtonsController(QVBoxLayout* layout_hall);
    ~HallButtonsController();

signals:
    // запросы этажа лифтов
    unsigned int request_floor_el1();
    unsigned int request_floor_el2();

    // запросы направления лифтов
    Controller::direction_t request_direction_el1();
    Controller::direction_t request_direction_el2();

    // передача этажей лифтам для принятия на обработку
    void hallButtonProcessingRequested_el1(uint);
    void hallButtonProcessingRequested_el2(uint);

    // объединение верхних запросов для обработки
    void elevatorDataRequested(uint floor1, uint floor2,
                               direction_t dir1, direction_t dir2);
    void requestProcessed(); // конец обработки
    void requestSent(); // обновление запроса
    void finished(); // конец работы

public slots:
    void processButtonClick(unsigned int floor);

private slots:
    void processElevatorData(unsigned floor1, unsigned floor2,
                             direction_t dir1, direction_t dir2);
    void requestElevatorData();
    void checkQueue();
    void arrive(unsigned int floor);
    void become_idle();

private:
    static unsigned calculate_weight(unsigned curr_floor, unsigned destination, Controller::direction_t& dir);

    controllerStatus status = IDLE;
    std::vector<unique_ptr<Button>> hall_buttons;
    unsigned floor = 1;

    std::queue<unsigned> requests;
};

#endif // HALL_BUTTONS_CONTROLLER_H
