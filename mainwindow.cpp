#include "mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(800, 480);
    setWindowIcon(QIcon(":/new/prefix1/res/bitbug_favicon.ico"));
    setWindowTitle("贪吃蛇");
    this->setStyleSheet("QMainWindow{border-image: url(:/new/prefix1/res/page2.jpg);}");

    for(int x=0; x==0 || x== 39; x+=39)
    {
        for(int y=0; y<24; y++)
        {
            QPushButton *btn = new QPushButton(this);
            btn->resize(SIZE, SIZE);
            btn->move(x * 20, y * 20);
            btn->setEnabled(false);
            btn->setStyleSheet("background-color: rgb(170, 170, 0);");
        }
    }

    for(int y=0; y==0 || y==23; y+=23)
    {
        for(int x=1; x<39; x++)
        {
            QPushButton *btn = new QPushButton(this);
            btn->resize(SIZE, SIZE);
            btn->move(x * 20, y * 20);
            btn->setEnabled(false);
            btn->setStyleSheet("background-color: rgb(170, 170, 0);");
        }
    }

    Snack_Init(5);

    my_timer = new QTimer(this);
    connect(my_timer, &QTimer::timeout, this, &MainWindow::snack_run);
    my_timer->start(500);

    dessert = new Dessert(this);
    dessert->makeDessert(head);

    dir = RIGHT;
}

MainWindow::~MainWindow()
{

}


void MainWindow::snack_run()
{
    switch (dir)
    {
        case UP:
        {
            Snack *node = new Snack(this);
            node->x = head->next->x;
            node->y = head->next->y - 20;
            node->btn = new QPushButton(this);
            node->btn->setFixedSize(20, 20);
            node->btn->move(node->x, node->y);
            node->next = head->next;
            head->next = node;
            break;
        }
        case RIGHT:
        {
            Snack *node = new Snack(this);
            node->x = head->next->x + 20;
            node->y = head->next->y;
            node->btn = new QPushButton(this);
            node->btn->setFixedSize(20, 20);
            node->btn->move(node->x, node->y);
            node->next = head->next;
            head->next = node;
            break;
        }
        case DOWN:
        {
            Snack *node = new Snack(this);
            node->x = head->next->x;
            node->y = head->next->y + 20;
            node->btn = new QPushButton(this);
            node->btn->setFixedSize(20, 20);
            node->btn->move(node->x, node->y);
            node->next = head->next;
            head->next = node;
            break;
        }
        case LEFT:
        {
            Snack *node = new Snack(this);
            node->x = head->next->x - 20;
            node->y = head->next->y;
            node->btn = new QPushButton(this);
            node->btn->setFixedSize(20, 20);
            node->btn->move(node->x, node->y);
            node->next = head->next;
            head->next = node;
            break;
        }
        default:
        break;
    }
    if(head->next->x < 20 || head->next->x >= 780 || head->next->y < 20 || head->next->y >= 460 || snake_crash())
    {
        my_timer->stop();
        this->setStyleSheet("QMainWindow{border-image: url(:/new/prefix1/res/gameover.png);}");
        return ;
    }
    else if(head->next->x == dessert->x*20 && head->next->y == dessert->y*20)
    {
        dessert->makeDessert(head);
    }
    else
    {
        Snack *p = head;
        while(p->next->next != NULL)
        {
            p = p->next;
        }
        delete(p->next->btn);
        delete(p->next);
        p->next = NULL;
    }
    setBackground();
}

void MainWindow::setBackground()
{
    switch (dir)
    {
        case UP:
        {
            head->next->btn->setStyleSheet("border-image: url(:/new/prefix1/res/up.png);");
            break;
        }
        case RIGHT:
        {
            head->next->btn->setStyleSheet("border-image: url(:/new/prefix1/res/right.png);");
            break;
        }
        case LEFT:
        {
            head->next->btn->setStyleSheet("border-image: url(:/new/prefix1/res/left.png);");
            break;
        }
        case DOWN:
        {
            head->next->btn->setStyleSheet("border-image: url(:/new/prefix1/res/down.png);");
            break;
        }
        default:
            break;
    }
    head->next->btn->show();

    Snack *pre = head->next;
    Snack *current = pre->next;
    Snack *next = current->next;
    while(next != NULL)
    {
        if(((pre->x<current->x) && (pre->y==current->y) && (current->x==next->x)&&(current->y>next->y))\
           || (next->x<current->x && current->y==next->y && pre->x==current->x && pre->y<current->y))
        {
            current->btn->setStyleSheet("border-image: url(:/new/prefix1/res/up_left.png);");
        }
        else if((pre->x<current->x && pre->y==current->y && current->x==next->x && current->y<next->y)\
           || (next->x<current->x && current->y==next->y && pre->x==current->x && pre->y>current->y))
        {
            current->btn->setStyleSheet("border-image: url(:/new/prefix1/res/left_down.png);");
        }
        else if((pre->x==current->x && pre->y>current->y && current->x<next->x && current->y==next->y)\
           || (next->x==current->x && current->y<next->y && pre->x>current->x && pre->y==current->y))
        {
            current->btn->setStyleSheet("border-image: url(:/new/prefix1/res/right_down.png);");
        }
        else if((pre->x==current->x && pre->y<current->y &&current->x<next->x && current->y==next->y)\
           || (next->x==current->x && current->y>next->y && pre->x>current->x && pre->y==current->y))
        {
            current->btn->setStyleSheet("border-image: url(:/new/prefix1/res/up_right.png);");
        }
        else
        {
            current->btn->setStyleSheet("border-image: url(:/new/prefix1/res/she.png);");
        }
        current->btn->show();
        pre = pre->next;
        current = current->next;
        next = next->next;
    }

    if((pre->x<current->x) && (pre->y==current->y))
    {
        current->btn->setStyleSheet("border-image: url(:/new/prefix1/res/tou_right.png);");
    }
    else if(pre->x>current->x && pre->y==current->y)
    {
        current->btn->setStyleSheet("border-image: url(:/new/prefix1/res/tou_left.png);");
    }
    else if(pre->x==current->x && pre->y>current->y)
    {
        current->btn->setStyleSheet("border-image: url(:/new/prefix1/res/tou_up.png);");
    }
    else if(pre->x==current->x && pre->y<current->y)
    {
        current->btn->setStyleSheet("border-image: url(:/new/prefix1/res/tou_down.png);");
    }
    current->btn->show();
}


void MainWindow::Snack_Init(int size)
{
    head = new Snack(this);
    head->x = 400;
    head->y = 240;
    head->next = NULL;

    Snack *p = NULL;
    while(size--)
    {
        p = head;
        while(p->next != NULL)
        {
            p = p->next;
        }

        Snack *node = new Snack(this);
        node->x = p->x - SIZE;
        node->y = p->y;
        node->btn = new QPushButton(this);
        node->btn->setFixedSize(SIZE, SIZE);
        node->btn->move(node->x, node->y);

        p->next = node;
        node->next = NULL;
    }

    //snack head
    p = head->next;
    p->btn->setStyleSheet("border-image: url(:/new/prefix1/res/right.png);");

    //snack body
    while(p->next->next != NULL)
    {
        p = p->next;
        p->btn->setStyleSheet("border-image: url(:/new/prefix1/res/she.png);");
    }

    //snack tail
    p->next->btn->setStyleSheet("border-image: url(:/new/prefix1/res/tou_left.png);");
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
        case Qt::Key_W:
        {
            if(dir != DOWN) dir = UP;
            break;
        }
        case Qt::Key_A:
        {
            if(dir != RIGHT) dir = LEFT;
            break;
        }
        case Qt::Key_D:
        {
            if(dir != LEFT) dir = RIGHT;
            break;
        }
        case Qt::Key_S:
        {
            if(dir != UP) dir = DOWN;
            break;
        }
        default:
            break;
    }
}

bool MainWindow::snake_crash()
{
    Snack *h = head->next;
    Snack *p = h->next;

    while (p != NULL)
    {
        if(h->x == p->x && h->y == p->y)
        {
            return true;
        }
        p = p->next;
    }
    return false;
}
