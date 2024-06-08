
#include <QDebug>
#include <QGridLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QVBoxLayout>

#include "HashTableCellWidget.h"

#include "HashTableWidget.h"

HashTableWidget::HashTableWidget(QWidget *parent)
    : QWidget(parent)
    , m_layout(new QGridLayout(this))
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(m_layout);
    setLayout(mainLayout);

    QMargins margins = m_layout->contentsMargins();
    //TODO: margin recalculating to fit all connections
    margins.setRight(margins.right() + 15);
    m_layout->setContentsMargins(margins);
}

HashTableWidget::~HashTableWidget()
{
}


int HashTableWidget::findRow(int key) const
{
    //TODO: implement
    return -1; //return m_hashTable.findRow(key);
}
void HashTableWidget::addRow(int key, const QString &value)
{
    if (!m_items.size())
    {
        return;
    }
    if(m_hashTable.insert(key, value.toStdString()))
    {
        int row = m_hashTable._findIndex(key);
        m_items[row].ptr->setKey(key);
        m_items[row].ptr->setValue(value);
        if(m_hashTable.m_table[row]->m_prev)
        {
            addConnection(m_hashTable._findIndex(m_hashTable.m_table[row]->m_prev), row);
        }
        update();
    }
}

bool HashTableWidget::removeRow(int key)
{
    if (!m_items.size())
    {
        return false;
    }
    int row = m_hashTable._findIndex(key);
    HashTable oldTable(m_hashTable);
    if(m_hashTable.erase(key))
    {
        if(m_items[row].ptr->key() == key)
        {
            if(!m_items[row].next && !m_items[row].prev)
            {
                m_items[row].ptr->emptyKey();
                m_items[row].ptr->setValue("");
            }
            else if(m_items[row].prev && !m_items[row].next)
            {
                m_items[row].ptr->emptyKey();
                m_items[row].ptr->setValue("");
                m_items[row].prev = nullptr;
                m_items[oldTable._findIndex(oldTable.m_table[row]->m_prev)].next = nullptr;
            }
            else if(m_items[row].next)
            {
                ItemData tmp = m_items[row];
                while(tmp.next && tmp.ptr->value() != "")
                {
                    tmp.ptr->setKey(tmp.next->key());
                    tmp.ptr->setValue(tmp.next->value());
                    row = oldTable._findIndex(oldTable.m_table[row]->m_next);
                    tmp = m_items[row];
                }
                tmp.ptr->emptyKey();
                tmp.ptr->setValue("");
                m_items[row].prev = nullptr;
                m_items[oldTable._findIndex(oldTable.m_table[row]->m_prev)].next = nullptr;
            }
            update();
        }
        else
        {
            ItemData tmp = m_items[row];
            while(tmp.ptr->key() != key)
            {
                row = oldTable._findIndex(oldTable.m_table[row]->m_next);
                tmp = m_items[row];
            }
            while(tmp.next && tmp.ptr->value() != "")
            {
                tmp.ptr->setKey(tmp.next->key());
                tmp.ptr->setValue(tmp.next->value());
                row = oldTable._findIndex(oldTable.m_table[row]->m_next);
                tmp = m_items[row];
            }
            tmp.ptr->emptyKey();
            tmp.ptr->setValue("");
            m_items[row].prev = nullptr;
            m_items[oldTable._findIndex(oldTable.m_table[row]->m_prev)].next = nullptr;
            update();
        }
    }
    return true;
}

void HashTableWidget::resize(int size)
{
    //TODO: implement
    int oldSize = m_items.size(); //= m_hashTable.capacity();
    for (int i = oldSize - 1; i >= size; --i) {
        delete m_items[i].ptr;
    }

    m_items.resize(size);
    for (int i = oldSize; i < size; ++i) {
        m_items[i].ptr = new HashTableCellWidget(this);
        //TODO: make empty rows uneditable by default
        connect(m_items[i].ptr, &HashTableCellWidget::valueChanged, this, &HashTableWidget::onValueChanged);
        m_layout->addWidget(m_items[i].ptr, i, 0);
    }
}

void HashTableWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    for (ItemData &item : m_items) {
        if (item.next) {
            item.connectionRect = item.baseConnectionRect(m_baseConnectionOffset);

            int rightBorderOffset = 0;
            QVector<int> rightBorders;
            for (const ItemData &other : qAsConst(m_items)) {
                if (&other == &item || !other.connectionRect.isValid()) {
                    continue;
                }

                if (other.connectionRect.intersects(item.connectionRect)) {
                    rightBorders.append(other.connectionRect.right());
                    while (rightBorders.contains(item.connectionRect.right() + rightBorderOffset)) {
                        rightBorderOffset += m_connectionOffset;
                    }
                }
            }
            item.connectionRect.setRight(item.connectionRect.right() + rightBorderOffset);

            if (event->rect().intersects(item.connectionRect)) {
                painter.drawLine(item.connectionRect.topLeft(), item.connectionRect.topRight());
                painter.drawLine(item.connectionRect.topRight(), item.connectionRect.bottomRight());
                painter.drawLine(item.connectionRect.bottomRight(), item.connectionRect.bottomLeft());
                //TODO: draw arrow
            }
        }
    }
    //TODO: resize widget / layout
}

void HashTableWidget::addConnection(int from, int to)
{
    m_items[from].next = m_items[to].ptr;
    m_items[to].prev = m_items[from].ptr;
}

void HashTableWidget::removeConnections(int itemIndex)
{
    if (m_items[itemIndex].prev) {
        m_items[itemIndex].prev = m_items[itemIndex].next;
    }
    m_items[itemIndex].prev = nullptr;
    m_items[itemIndex].next = nullptr;
}

void HashTableWidget::onValueChanged(HashTableCellWidget *item)
{
    m_hashTable[item->key()] = item->value().toStdString();
}

QRect HashTableWidget::ItemData::baseConnectionRect(int connectionOffset) const
{
    return baseConnectionRect(ptr, next, connectionOffset);
}

QRect HashTableWidget::ItemData::baseConnectionRect(HashTableCellWidget *from, HashTableCellWidget *to, int connectionOffset)
{
    if (!from || !to) {
        return QRect();
    }

    QPoint startPos = from->pos();
    startPos.rx() += from->width();
    startPos.ry() += from->height() / 3 * 2;
    QPoint endPos = to->pos();
    endPos.rx() += to->width();
    endPos.ry() += to->height() / 3;

    QRect rect;
    rect.setTopLeft(startPos);
    rect.setBottom(endPos.y());
    rect.setRight(qMax(startPos.x(), endPos.x()) + connectionOffset);
    return rect;
}
