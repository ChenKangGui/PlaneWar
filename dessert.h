#ifndef DESSERT_H
#define DESSERT_H

#include <ctime>
#include <QPushButton>
#include <QMainWindow>
#include "snack.h"

class Snack;

class Dessert
{
public:
    Dessert(QMainWindow *parent);
    ~Dessert();

    int x;
    int y;
    QPushButton *btn;

    void makeDessert();
    void makeDessert(Snack *h);
};

#endif // DESSERT_H
