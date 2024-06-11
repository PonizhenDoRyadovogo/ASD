#pragma once

#include <QWidget>
#include <QVector>

#include"../HashTable/HashTable/HashTable.h"

class QGridLayout;
class HashTableCellWidget;

class HashTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HashTableWidget(QWidget *parent = nullptr);
    ~HashTableWidget() = default;

    void findRow(int key);
public slots:
    void addRow(int key, const QString &value);
    bool removeRow(int key);
    void resize(int newSize);

protected:
    void paintEvent(QPaintEvent *event) override;
private:
    HashTableCellWidget* findCell(const int key) const;
    void setEmpty(HashTableCellWidget* cell);
private slots:
    void addConnection(int from, int to);
    void removeConnections(int itemIndex);
    void onValueChanged(HashTableCellWidget *item);

private:
    struct ItemData
    {
        HashTableCellWidget *ptr = nullptr;
        HashTableCellWidget *prev = nullptr;
        HashTableCellWidget *next = nullptr;

        QRect connectionRect;
        QRect baseConnectionRect(int connectionOffset) const;
        static QRect baseConnectionRect(HashTableCellWidget *from, HashTableCellWidget *to, int connectionOffset);
    };

    QVector<ItemData> m_items;
    QGridLayout *m_layout = nullptr;
    int m_baseConnectionOffset = 10;
    int m_connectionOffset = 10;
    HashTable m_hashTable;
    HashTableCellWidget* m_targetCell = nullptr;
    int m_maxRight = 0;
};

