#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "accountstablemodel.h"
#include "newclientdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void timeAddButtonSignal(QString name, qint32 time);

private slots:
    void on_addNewClientButton_clicked();

    void on_addTimeButton_clicked();

private:
    Ui::MainWindow *ui;
    accountsTableModel *clientsModel;
    newClientDialog *newClientForm;
};
#endif // MAINWINDOW_H
