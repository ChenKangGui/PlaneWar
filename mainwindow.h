#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QRect>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QTime>
#include <QTimer>
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include "snack.h"
#include "dessert.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QTimer *my_timer;
    Snack *head;
    Dessert *dessert;
    Director dir;


    void setBackground();

    void keyPressEvent(QKeyEvent *e);
    void Snack_Init(int size);
    bool snake_crash();

public slots:
    void snack_run();
};

#endif // MAINWINDOW_H


