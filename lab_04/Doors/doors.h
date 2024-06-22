#ifndef DOORS_H
#define DOORS_H

#include <QObject>
#include <QTimer>

class Doors: public QObject
{
    Q_OBJECT
    using doorsStatus = enum
    {
        OPEN, CLOSED, OPENING, CLOSING
    };

public:
    explicit Doors();

signals:
    void startClosingSignal();
    void startOpeningSignal();

    void doorsClosed();
    void doorsOpen();


public slots:
    void startClosing();
    void startOpening();

private slots:
    void open();
    void close();

private:
    doorsStatus status = CLOSED;

    QTimer opening_timer;
    QTimer closure_timer;
    QTimer waiting_timer;
};

#endif // DOORS_H
