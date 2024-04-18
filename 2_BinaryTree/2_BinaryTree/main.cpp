#include <iostream>
#include <vector>
#include"BinaryTree.h"
#include "BinaryTreeTester.h"

int main()
{
    srand(time(0));
    BinaryTreeTester tester(false, true);
    tester.test(1000);
    return 0;

    BinaryTree foo, goo;
    {
        for (int i = 0; i < 10; ++i)
        {
            foo.add(i);
        }
    }
    foo.printHorizontal();
    std::cout << "=======\n";
    for (int i = 0; i < 10; ++i)
    {
        foo.remove(i);
        foo.printHorizontal();
        std::cout << "size = "<< foo.size() << "\n=======\n";
    }
    foo.remove(0);
    //foo.printHorizontal();
    std::cout << "=======\n";
    return 0;
    std::vector<int> vec = foo.treeToVector();
    for (int i : vec)
    {
        std::cout << i << " ";
    }
    std::cout << "\nmin = " << foo.min();
    std::cout << "\nmax = " << foo.max() << "\n";
    std::cout << "level 5 = " << foo.level(5);
    if (foo.isBalanced() == true)
        std::cout << "balanced";
    else
        std::cout << "not balanced";
    //foo.printHorizontal();
    return 0;
    goo = foo;
    goo.printHorizontal();
    //foo.clearChildren(foo.find(1));
    //foo.printHorizontal();
    std::cout << "=======\n";
    foo.clone(foo.find(1)).printHorizontal();
    return 0;
}

//#include <stdlib.h>
//
//#include <QApplication>
//#include <QDebug>
//#include<QGraphicsPixmapItem>
//#include<QGraphicsView>
//#include "TreeWidget.h"
//
//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);
//    TreeWidget widget;
//    widget.show();
//    for (int i = 0; i < 20; ++i) {
//        widget.addKey(rand() % 100);
//    }
//    return app.exec();
//}
