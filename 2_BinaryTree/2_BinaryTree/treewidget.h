#pragma once

#include <QWidget>
#include "BinaryTree.h"
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
protected:
    void resizeEvent(QResizeEvent *event)override;
private:
    void _updateSceneRect();
    void _redrawTree();
    QPointF _drawTree(BinaryTree::Node* root, int leftBorderPos, int rightBorderPos, int yPos);
private:
    Ui::TreeWidget *ui;
    BinaryTree *m_tree = nullptr;
    QGraphicsScene *m_scene = nullptr;
    int m_fontSize = 22;
};

