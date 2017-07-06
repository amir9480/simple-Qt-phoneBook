#ifndef CONTACTDB_H
#define CONTACTDB_H

#include <QtCore>
#include <QtSql>

#include "phonebooklibrary_global.h"
#include "contactdetail.h"

// جهت برقراری ارتباط با دیتابیس
class PHONEBOOKLIBRARYSHARED_EXPORT ContactDB
{
public:
    ContactDB();
    virtual ~ContactDB();

    //! اضافه کردن مخاطب جدید به دفترچه تلفن
    void                    addContact(const ContactDetail& _d);

    //! شمارش تعداد کل مخاطبین
    int                     countAll();

    //! پیدا کردن مخاطبی بر اساس یک رشته و تمام مشخصات ممکن مخاطب
    QList<ContactDetail>    findContact(QString _val);

    //! تهیه تمام مخاطبین
    QList<ContactDetail>    getAll();

    //! تهیه مشخصات یک کاربر بر اساس آی دی مخاطب
    ContactDetail           getContact(int id);

    //! تهیه مشخصات یک مخاطب بر اساس مکان یا ایندکس حضور آن در تمامی مخاطبین
    ContactDetail           getContactAtIndex(int _index);

    //! حزف یک مخاطب با آی دی آن
    void                    removeContact(int _id);

    //! بروز رسانی مشخصات یک مخاطب بر اساس آی دی آن
    void                    updateContact(int _id,const ContactDetail& _d);


protected:
    // SQL جهت اجرای دستورات
    QSqlQuery mQuery;
};

#endif // CONTACTDB_H
