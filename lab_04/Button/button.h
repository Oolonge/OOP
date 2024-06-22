#ifndef BUTTON_H
#define BUTTON_H
#include <QPushButton>

class Button : public QPushButton
{
    Q_OBJECT

    using buttonStatus = enum
    {
        PRESSED, INACTIVE
    };

public:
    Button(unsigned int floor);

signals:
    void _pressed(unsigned int);
    void _unpressed();

public slots:
    void press();
    void unpress();

private:
    buttonStatus status = INACTIVE;
    unsigned int floor;
};

#endif // BUTTON_H
