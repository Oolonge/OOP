#include "button.h"
#include "iostream"
#include "definitions.h"

using namespace std;

Button::Button(unsigned int floor): floor(floor)
{
    this->setText(QString::number(floor));
    this->setStyleSheet(STYLE_INACTIVE);

    QObject::connect(this, SIGNAL(clicked()), dynamic_cast<Button*>(this), SLOT(press()));
    QObject::connect(this, SIGNAL(_unpressed()), this, SLOT(unpress()));
}

void Button::press()
{
    if (status == PRESSED)
        return;
    status = PRESSED;

    this->setStyleSheet(STYLE_ACTIVE);
    this->update(); // qt сам должен обновить, теоретически

    cout << "Произошел вызов лифта на этаже №" + std::to_string(floor) << endl;

    emit _pressed(floor);
}

void Button::unpress()
{
    if (status == INACTIVE)
        return;

    status = INACTIVE;

    this->setStyleSheet(STYLE_ELEVATOR);
    this->update();
}
