QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../3_BinaryTreeSearch/3_BinaryTreeSearch/BinaryTreeSearch.cpp \
    ../3_BinaryTreeSearch/3_BinaryTreeSearch/SearchTreeTester.cpp \
    ../2_BinaryTree/2_BinaryTree/BinaryTree.cpp \
    ../2_BinaryTree/2_BinaryTree/BinaryTreeTester.cpp \
    ../4_BalancedSearchTree/4_BalancedSearchTree/BalancedSearchTree.cpp \
    ../4_BalancedSearchTree/4_BalancedSearchTree/BalancedSearchTreeTester.cpp \
    GraphicsItemNode.cpp \
    QTmain.cpp \
    treewidget.cpp

HEADERS += \
    ../3_BinaryTreeSearch/3_BinaryTreeSearch/BinaryTreeSearch.h \
    ../3_BinaryTreeSearch/3_BinaryTreeSearch/SearchTreeTester.h \
    ../2_BinaryTree/2_BinaryTree/BinaryTree.h \
    ../2_BinaryTree/2_BinaryTree/BinaryTreeTester.h \
    ../4_BalancedSearchTree/4_BalancedSearchTree/BalancedSearchTree.h \
    ../4_BalancedSearchTree/4_BalancedSearchTree/BalancedSearchTreeTester.h \
    GraphicsItemNode.h \
    treewidget.h

FORMS += \
    treewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
