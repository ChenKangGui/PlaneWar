#ifndef SNACK_H
#define SNACK_H

#include <QRect>
#include <QPushButton>
#include <QPixmap>
#include <QMainWindow>

#define SIZE 20

enum Director
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

class Snack
{
public:
    Snack(QMainWindow *parent);
    ~Snack();
    int x;
    int y;
    QPushButton *btn;

    Snack *next;
};

#endif // SNACK_H
