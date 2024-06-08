#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->hashTable->resize(ui->spinBox_tableSize->value());

    connect(ui->pushButton_add, &QPushButton::clicked, this, [this]() {
        ui->hashTable->addRow(ui->spinBox_key->value(), ui->lineEdit_value->text());
    });
    connect(ui->pushButton_remove, &QPushButton::clicked, this, [this]() {
        ui->hashTable->removeRow(ui->spinBox_key->value());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
