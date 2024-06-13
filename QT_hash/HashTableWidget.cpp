#include <QDebug>
#include <QGridLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QVBoxLayout>
#include <QSound>

#include "HashTableCellWidget.h"

#include "HashTableWidget.h"

HashTableWidget::HashTableWidget(QWidget *parent)
    : QWidget(parent)
    , m_layout(new QGridLayout)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(m_layout);
    setLayout(mainLayout);
}

void HashTableWidget::findRow(int key)
{
    m_targetCell = findCell(key);
    update();
}

void HashTableWidget::addRow(int key, const QString &value)
{
    if (!m_items.size())
    {
        return;
    }
    if(m_hashTable.insert(key, value.toStdString()))
    {
        QSound::play("C:/Users/User/Downloads/add.wav");
        int row = m_hashTable._findIndex(key);
        m_items[row].ptr->setKey(key);
        m_items[row].ptr->setValue(value);
        m_items[row].ptr->setEditable(true);
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
                setEmpty(m_items[row].ptr);
                if(m_items[row].ptr == m_targetCell)
                {
                    m_targetCell = nullptr;
                }
            }
            else if(m_items[row].prev && !m_items[row].next)
            {
                setEmpty(m_items[row].ptr);
                m_items[row].prev = nullptr;
                m_items[oldTable._findIndex(oldTable.m_table[row]->m_prev)].next = nullptr;
                if(m_items[row].ptr == m_targetCell)
                {
                    m_targetCell = nullptr;
                }
            }
            else if(m_items[row].next)
            {
                if(m_items[row].ptr == m_targetCell)
                {
                    m_targetCell = nullptr;
                }
                ItemData tmp = m_items[row];
                while(tmp.next && tmp.ptr->value() != "")
                {
                    tmp.ptr->setKey(tmp.next->key());
                    tmp.ptr->setValue(tmp.next->value());
                    row = oldTable._findIndex(oldTable.m_table[row]->m_next);
                    tmp = m_items[row];
                    if(tmp.ptr == m_targetCell)
                    {
                        m_targetCell = tmp.prev;
                    }
                }
                setEmpty(m_items[row].ptr);
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
            setEmpty(m_items[row].ptr);
            m_items[row].prev = nullptr;
            m_items[oldTable._findIndex(oldTable.m_table[row]->m_prev)].next = nullptr;
            update();
        }
        return true;
    }
    else
    {
        return false;
    }
}

void HashTableWidget::resize(int newSize)
{
    if(m_items.size() == newSize)
    {
        return;
    }
    QVector<ItemData> oldTable(m_items.size());
    qSwap(m_items, oldTable);
    m_items.resize(newSize);
    for(int i = 0; i < newSize; ++i)
    {
        m_items[i].ptr = new HashTableCellWidget(this);
        connect(m_items[i].ptr, &HashTableCellWidget::valueChanged, this, &HashTableWidget::onValueChanged);
        m_layout->addWidget(m_items[i].ptr, i, 0);
    }
    m_hashTable.resize(newSize);
    for(int i = 0; i < oldTable.size(); ++i)
    {
        if(oldTable[i].ptr->value() != "")
        {
            int row = m_hashTable._findIndex(oldTable[i].ptr->key());
            if(row >= 0)
            {
                m_items[row].ptr->setKey(oldTable[i].ptr->key());
                m_items[row].ptr->setValue(oldTable[i].ptr->value());
                m_items[row].ptr->setEditable(true);
                if(m_hashTable.m_table[row]->m_prev)
                {
                    addConnection(m_hashTable._findIndex(m_hashTable.m_table[row]->m_prev), row);
                }
                if(oldTable[i].ptr == m_targetCell)
                {
                    m_targetCell = m_items[row].ptr;
                }
            }
            else
            {
                if(oldTable[i].ptr == m_targetCell)
                {
                    m_targetCell = nullptr;
                }
            }
        }
        delete oldTable[i].ptr;
    }
    update();
}

void HashTableWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    int oldMaxRight = m_maxRight;
    QPainter painter(this);
    for (ItemData &item : m_items) {
        if(m_targetCell && m_targetCell->value() == item.ptr->value())
        {
            painter.fillRect(item.ptr->x(), item.ptr->y(), item.ptr->width(), item.ptr->height(), Qt::red);
            QWidget::paintEvent(event);
        }

        if (item.next) {
            item.connectionRect = item.baseConnectionRect(m_baseConnectionOffset);

            int rightBorderOffset = 0;
            QVector<int> rightBorders;
            for (const ItemData &other : qAsConst(m_items)) {
                if (&other == &item) {
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

            m_maxRight = qMax(m_maxRight, item.connectionRect.right());
            if (event->rect().intersects(item.connectionRect)) {
                painter.drawLine(item.connectionRect.topLeft(), item.connectionRect.topRight());
                painter.drawLine(item.connectionRect.topRight(), item.connectionRect.bottomRight());
                painter.drawLine(item.connectionRect.bottomRight(), item.connectionRect.bottomLeft());
                //draw arrow
                painter.drawLine(item.connectionRect.bottomLeft().rx(), item.connectionRect.bottomLeft().ry(),
                                item.connectionRect.bottomLeft().rx() + 5, item.connectionRect.bottomLeft().ry() - 5);
                painter.drawLine(item.connectionRect.bottomLeft().rx(), item.connectionRect.bottomLeft().ry(),
                                 item.connectionRect.bottomLeft().rx() + 5, item.connectionRect.bottomLeft().ry() + 5);
            }
        }
    }

    if(oldMaxRight < m_maxRight)
    {
        QMargins margins = m_layout->contentsMargins();
        margins.setRight(m_maxRight - width() + 20);
        m_layout->setContentsMargins(margins);
    }
}

HashTableCellWidget* HashTableWidget::findCell(const int key) const
{
    int row = m_hashTable.m_hashFunction->hash(key, m_hashTable.capacity());
    if(m_hashTable.m_table[row]->m_hasValue)
    {
        if(m_items[row].ptr->key() == key)
        {
            return m_items[row].ptr;
        }
        else
        {
            if(m_items[row].next)
            {
                ItemData tmp = m_items[row];
                while(tmp.next)
                {
                    row = m_hashTable._findIndex(m_hashTable.m_table[row]->m_next);
                    tmp = m_items[row];
                    if(tmp.ptr->key() == key)
                    {
                        return tmp.ptr;
                    }
                }
                return nullptr;
            }
            else
            {
                return nullptr;
            }
        }
    }
    else
    {
        return nullptr;
    }
}

void HashTableWidget::setEmpty(HashTableCellWidget* cell)
{
    cell->emptyKey();
    cell->setValue("");
    cell->setEditable(false);
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
