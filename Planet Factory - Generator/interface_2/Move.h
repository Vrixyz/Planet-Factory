#ifndef MOVE_H
#define MOVE_H

#include <QThread>

class Move : public QThread
{
    Q_OBJECT
private:
    void run();
};

#endif // MOVE_H
