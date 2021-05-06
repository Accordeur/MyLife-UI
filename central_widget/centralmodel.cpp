#include "centralmodel.h"

CentralModel::CentralModel(QObject* parent) : QAbstractItemModel(parent)
{

}

QVariant CentralModel::data(const QModelIndex &index, int role) const {
    return {};
}
QVariant CentralModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const {
    return {};
}

QModelIndex CentralModel::index(int row, int column,
                                const QModelIndex &parent) const {
    return {};
}
QModelIndex CentralModel::parent(const QModelIndex &index) const {
    return {};
}

int CentralModel::rowCount(const QModelIndex &parent) const {
    return {};
}
int CentralModel::columnCount(const QModelIndex &parent) const {
    return {};
}

Qt::ItemFlags CentralModel::flags(const QModelIndex &index) const {
    return {};
}
bool CentralModel::setData(const QModelIndex &index, const QVariant &value,
                           int role) {
    return {};
}
bool CentralModel::setHeaderData(int section, Qt::Orientation orientation,
                                 const QVariant &value, int role) {
    return {};
}

bool CentralModel::insertColumns(int position, int columns,
                                 const QModelIndex &parent) {
    return {};
}
bool CentralModel::removeColumns(int position, int columns,
                                 const QModelIndex &parent) {
    return {};
}
bool CentralModel::insertRows(int position, int rows,
                              const QModelIndex &parent) {
    return {};
}
bool CentralModel::removeRows(int position, int rows,
                              const QModelIndex &parent) {
    return {};
}
