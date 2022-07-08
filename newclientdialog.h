#ifndef NEWCLIENTDIALOG_H
#define NEWCLIENTDIALOG_H

#include <QDialog>
#include <QDateTime>

namespace Ui {
class newClientDialog;
}

class newClientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit newClientDialog(QWidget *parent = nullptr);
    ~newClientDialog();

private:
    Ui::newClientDialog *ui;

signals:
    void catchNewClient(QString name, QDateTime startDate, qint64 monthesPaid);
private slots:
    void on_doneButton_clicked();
};

#endif // NEWCLIENTDIALOG_H
