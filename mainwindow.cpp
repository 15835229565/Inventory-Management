#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    inventory(new InventoryWidget(this)),
    users(new UsersWidget(this))
{
    qDebug() << "[Main Window] Constructing...";
    ui->setupUi(this);

    ui->tabWidget->addTab(inventory, tr("Inventory"));
    ui->tabWidget->addTab(users, tr("Users"));
}

MainWindow::~MainWindow()
{
    qDebug() << "[Main Window] Destructing...";
    delete ui;
    delete users;
}
