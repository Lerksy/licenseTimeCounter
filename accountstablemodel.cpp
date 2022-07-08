#include "accountstablemodel.h"
#include <QSqlError>

void accountsTableModel::dbFirstRun(){
    QSqlQuery initQuery;
    initQuery.exec("CREATE TABLE IF NOT EXISTS Clients(Name varchar(255), startDate bigint, monthsPaid integer, accAmount integer, tariff integer);");
}

void accountsTableModel::loadDataFromDB(){
    QSqlQuery loadQuery;
    loadQuery.exec("SELECT COUNT(*) FROM Clients");
    loadQuery.next();
    ROWS = loadQuery.value(0).toInt();
    loadQuery.exec("SELECT * FROM Clients");
    clients->clear();
    while (loadQuery.next()) {
        clients->push_back(client(loadQuery.value("Name").toString(),
                                  loadQuery.value("startDate").toULongLong(),
                                  loadQuery.value("monthsPaid").toInt()));
    }

}

QDate accountsTableModel::expiryDate(qint64 index) const{
    QDate boughtDay = clients->at(index).startDate;
    qint64 monthes = clients->at(index).monthesPaid;
    return boughtDay.addMonths(monthes);
}

accountsTableModel::accountsTableModel(){
    clients = new QList<client>;
    QString dbName = QApplication::applicationDirPath()+"/data.db";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    QFileInfo dbInfo(dbName);
    if(!dbInfo.exists()){
        db.open();
        dbFirstRun();
    }else{
        db.open();
        loadDataFromDB();
    }

}

int accountsTableModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent)
    return ROWS;
}

int accountsTableModel::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent)
    return COLS;
}

QVariant accountsTableModel::data(const QModelIndex &index, int role) const{
    if (role == Qt::DisplayRole && checkIndex(index)){
        switch (index.column()) {
        default:{
            return QVariant();
        }
        case 0:{
            return clients->at(index.row()).name;
            break;
        }
        case 1:{
            QDate today(QDate::currentDate());
            QDate expireDate = expiryDate(index.row());
            qint64 diff = today.daysTo(expireDate);
            return diff;
        }
        case 2:{
            QDate today(QDate::currentDate());
            QDate expireDate = expiryDate(index.row());
            qint64 diff = today.daysTo(expireDate);
            return "~ "+QString::number(static_cast<double>(diff)/30);
        }
        case 3:{
            QDate expireDate = expiryDate(index.row());
            return expireDate.toString("dd MMM yyyy");
        }
        }
    }
    return QVariant();
}

QVariant accountsTableModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return "Name of Client";
        case 1:
            return "Subscription days left";
        case 2:
            return "Subscription monthes left";
        case 3:
            return "Next date of payment";
        default:
            break;
        }
    }else if(orientation == Qt::Vertical){
        return section+1;
    }
    return QVariant();
}

QStringList accountsTableModel::getNames(){
    QStringList names;
    for(const auto &i: *clients){
        names.push_back(i.name);
    }
    return names;
}

void accountsTableModel::addClient(QString name, QDateTime startDate, qint32 monthesPaid){
    beginResetModel();
    QSqlQuery pushQuery;
    pushQuery.exec(QString("INSERT INTO Clients(Name, startDate, monthsPaid) VALUES('%1', '%2', '%3');").arg(name).arg(startDate.toSecsSinceEpoch()).arg(monthesPaid));
    qDebug()<<pushQuery.lastError();
    loadDataFromDB();
    endResetModel();
}

void accountsTableModel::addTime(QString name, qint32 time){
    beginResetModel();
    QSqlQuery getQuery;
    getQuery.exec(QString("SELECT monthsPaid FROM Clients WHERE Name='%1'").arg(name));☻
    getQuery.next();
    qint32 pastTime = getQuery.value("monthsPaid").toInt();
    qint32 newTime = pastTime + time;
    QSqlQuery pushQuery;
    pushQuery.exec(QString("UPDATE Clients SET monthsPaid='%1' WHERE Name='%2'").arg(newTime).arg(name));
    loadDataFromDB();
    endResetModel();
}

void accountsTableModel::reloadModel(){
    beginResetModel();
    loadDataFromDB();
    endResetModel();
}
