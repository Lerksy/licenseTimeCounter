#include "newclientdialog.h"
#include "ui_newclientdialog.h"

newClientDialog::newClientDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newClientDialog)
{
    ui->setupUi(this);
}

newClientDialog::~newClientDialog()
{
    delete ui;
}

void newClientDialog::on_doneButton_clicked(){
    QString name = ui->nameEdit->text();
    QDateTime startDate = ui->startDateEdit->dateTime();
    qint64 monthesPaid = ui->monthesPaidSpinBox->value();
    emit catchNewClient(name, startDate, monthesPaid);
    this->close();
}

