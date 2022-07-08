#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clientsModel = new accountsTableModel();
    ui->clientsTableView->setModel(clientsModel);
    newClientForm = new newClientDialog(this);
    ui->clientsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->nameCombo->addItems(clientsModel->getNames());
    QObject::connect(newClientForm, &newClientDialog::catchNewClient, clientsModel, &accountsTableModel::addClient);
    QObject::connect(clientsModel, &QAbstractTableModel::modelReset, this, [&]{
        ui->nameCombo->clear();
        ui->nameCombo->addItems(clientsModel->getNames());
    });
    QObject::connect(this, &MainWindow::timeAddButtonSignal, clientsModel, &accountsTableModel::addTime);
    QObject::connect(ui->reloadModelButton, &QAbstractButton::clicked, clientsModel, &accountsTableModel::reloadModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addNewClientButton_clicked(){
    newClientForm->show();
}

void MainWindow::on_addTimeButton_clicked(){
    QString name = ui->nameCombo->currentText();
    qint32 monthesToAdd = ui->addTimeSpinBox->value();
    emit timeAddButtonSignal(name, monthesToAdd);
}

