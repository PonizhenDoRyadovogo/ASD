#pragma once

#include <QWidget>
#include "../2_BinaryTree/2_BinaryTree/BinaryTree.h"
//#include "../../3_BinaryTreeSearch/3_BinaryTreeSearch/BinaryTreeSearch.h"
class QGraphicsScene;

namespace Ui {
class TreeWidget;
}

class TreeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TreeWidget(QWidget *parent = nullptr);
    ~TreeWidget();

    void show();
public slots:
    void addKey(int key);
    void removeKey(int key);
    void changeTree(int index);
    void findKey(int key);
    //int calculateBalance(BinaryTree::Node* root);
    void clearScene();
protected:
    void resizeEvent(QResizeEvent *event)override;
private:
    void _updateSceneRect();
    void _redrawTree(BinaryTree::Node* targetNode = nullptr);
    QPointF _drawTree(BinaryTree::Node* root, int leftBorderPos, int rightBorderPos, int yPos, BinaryTree::Node* targetNode = nullptr);
private:
    Ui::TreeWidget *ui;
    BinaryTree *m_tree = nullptr;
    QGraphicsScene *m_scene = nullptr;
    int m_fontSize = 22;
};

