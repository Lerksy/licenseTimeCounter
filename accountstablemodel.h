#ifndef ACCOUNTSTABLEMODEL_H
#define ACCOUNTSTABLEMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include <QApplication>
#include <QFileInfo>

class accountsTableModel : public QAbstractTableModel
{
private:
    struct client{
        QString name;
        QDate startDate;
        qint64 monthesPaid;
        qint64 accAmount;
        qint64 pricePerAcc; // rubles

        client(QString name, quint64 startDate, qint64 monthesPaid){
            this->name = name;
            this->startDate = QDateTime::fromSecsSinceEpoch(startDate).date();
            this->monthesPaid = monthesPaid;
        }

    };
    QSqlDatabase db;
    QList<client> *clients;
    const int COLS = 4;
    int ROWS = 0;
    void dbFirstRun();
    void loadDataFromDB();
    QDate expiryDate(qint64 index) const;

public:
    accountsTableModel();
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QStringList getNames();

public slots:
    void addClient(QString name, QDateTime startDate, qint32 monthesPaid);
    void addTime(QString name, qint32 time);
    void reloadModel();
};

#endif // ACCOUNTSTABLEMODEL_H
