#include<QGraphicsScene>
#include "treewidget.h"
#include "ui_treewidget.h"
#include "GraphicsItemNode.h"
#include "../2_BinaryTree/2_BinaryTree/BinaryTree.cpp"
#include "../3_BinaryTreeSearch/3_BinaryTreeSearch/BinaryTreeSearch.h"
#include"../4_BalancedSearchTree/4_BalancedSearchTree/BalancedSearchTree.h"

TreeWidget::TreeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TreeWidget),
    m_tree(new BinaryTree),
    m_scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(m_scene);
    m_tree = new BinaryTree();
    QStringList list_items;
    list_items<<"BinaryTree"<<"BinaryTreeSearch"<<"BalancedSearchTree";
    ui->comboBox->addItems(list_items);
    connect(ui->pushButtonAdd, &QPushButton::clicked, this, [this](){addKey(ui->spinBox->value());});
    connect(ui->pushButtonDelete, &QPushButton::clicked, this, [this] {removeKey(ui->spinBox->value());});
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, [this] { changeTree(ui->comboBox->currentIndex()); });
    connect(ui->pushButtonFind, &QPushButton::clicked, this, [this](){findKey(ui->spinBox->value());});
}

TreeWidget::~TreeWidget()
{
    delete ui;
    delete m_tree;
}

void TreeWidget::show()
{
    QWidget::show();
    _updateSceneRect();
}
void TreeWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    _updateSceneRect();
}

void TreeWidget::addKey(int key)
{
    m_tree->add(key);
    _redrawTree();
}

void TreeWidget::removeKey(int key)
{
    m_tree->remove(key);
    _redrawTree();
}

void TreeWidget::changeTree(int index)
{
    std::vector<int> treeVec = m_tree->LRR();
    delete m_tree;
    if(index == 0)
    {
        m_tree = new BinaryTree;
    }
    else if(index == 1)
    {
        m_tree = new BinaryTreeSearch;
    }
    else if(index == 2)
    {
        m_tree = new BalancedSearchTree;
    }

    for(int i : treeVec)
    {
        m_tree->add(i);
    }
    _redrawTree();
}

void TreeWidget::findKey(int key)
{
    BinaryTree::Node* targetNode = m_tree->find(key);
    _redrawTree(targetNode);
}

QPointF TreeWidget::_drawTree(BinaryTree::Node *root, int leftBorderPos, int rightBorderPos, int yPos, BinaryTree::Node* targetNode)
{
    if (root == nullptr) {
        return QPointF();
    }
    int xPos = (leftBorderPos + rightBorderPos) / 2;
    GraphicsItemNode *item = new GraphicsItemNode(QString::number(root->getKey()));
    item->setFontSize(m_fontSize);

    if(root == targetNode)
    {
        item->setFillColor(Qt::red);
        item->update();
    }
    m_scene->addItem(item);
    item->setPos(xPos - item->boundingRect().width() / 2, yPos);
    QPointF center = item->pos() + QPointF(item->boundingRect().center());
    QPointF leftCenter = _drawTree(root->getLeft(), leftBorderPos, xPos, yPos + 75, targetNode);
    QPointF rightCenter = _drawTree(root->getRight(), xPos, rightBorderPos, yPos + 75, targetNode);

    if (!leftCenter.isNull()) {
        auto *line = m_scene->addLine(QLineF(center, leftCenter), QPen(Qt::red));
        line->setZValue(-1);
    }

    if (!rightCenter.isNull()) {
        auto *line = m_scene->addLine(QLineF(center, rightCenter), QPen(Qt::red));
        line->setZValue(-1);
    }

    return center;
}

void TreeWidget::_redrawTree(BinaryTree::Node* targetNode)
{
    m_scene->clear();
    _drawTree(m_tree->root(), 0, m_scene->width(), 0, targetNode);
}

void TreeWidget::_updateSceneRect()
{
    m_scene->setSceneRect(0, 0, qMax(int(m_scene->width()), ui->graphicsView->viewport()->width()),qMax(int(m_scene->height()), ui->graphicsView->viewport()->height()));
    _redrawTree();
}
