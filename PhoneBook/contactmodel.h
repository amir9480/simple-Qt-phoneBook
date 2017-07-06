#ifndef COTACTMODEL_H
#define COTACTMODEL_H


#include "contactdb.h"

#include <QtCore>
#include <QtWidgets>

// این مدلی هست جدول ما محتویاتش رو از این جا تهیه میکنه
class ContactModel : public QAbstractTableModel
{
public:
    ContactModel();
    virtual ~ContactModel();

    // انجام جستجو
    void do_search(QString _val);

    // تعداد سطر ها
    int rowCount(const QModelIndex &parent) const;

    // تعداد ستون ها
    int columnCount(const QModelIndex &parent) const;

    // محتویات داخل جدول
    QVariant data(const QModelIndex &index, int role) const;

    // محتویات سر تیتر جدول
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    // تهیه ی مدیریت کننده
    ContactDB& getDB();

    bool getIs_searching() const;
    void setIs_searching(bool value);

protected:
    // مدیریت کننده مخاطبین
    mutable ContactDB mDB;

    //! نتیجه جستجو توی این نگه داری میشه
    QList<ContactDetail> mSearchResult;

    //! آیا هم اکنون در حال جستجو کردن هست
    bool is_searching;
};

#endif // COTACTMODEL_H
