#include <stdlib.h>

#include <QApplication>
#include <QDebug>
#include<QGraphicsPixmapItem>
#include<QGraphicsView>
#include "TreeWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TreeWidget widget;
    widget.show();
    for (int i = 0; i < 20; ++i) {
        widget.addKey(rand() % 100);
    }
    return app.exec();
}
