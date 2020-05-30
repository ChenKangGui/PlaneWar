#include "dessert.h"

Dessert::Dessert(QMainWindow *parent)
{
    x = 0;
    y = 0;
    btn = new QPushButton(parent);
    btn->setFixedSize(20, 20);
    btn->setStyleSheet("border-image: url(:/new/prefix1/res/eat.ico);");

    srand((unsigned)time(NULL));
}


void Dessert::makeDessert(Snack *h)
{
    bool circle = false;
    Snack *p = NULL;
    while(1)
    {
        x = rand()%38+1;
        y = rand()%22+1;
        btn->move(x * 20, y * 20);

        p = h->next;
        while (p != NULL)
        {
            if(p->x == x && p->y == y)
            {
                circle = true;
                break;
            }
            p = p->next;
        }
        if(!circle)  break;
    }
}
