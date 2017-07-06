#ifndef CONTACTDETAIL_H
#define CONTACTDETAIL_H

#include <QtCore>
#include <QtSql>
#include "phonebooklibrary_global.h"

//! جهت نگهداری محتویات هر آیتم از دیتابیس استفاده میشود
//!
//! PHONEBOOKLIBRARYSHARED_EXPORT
//! جهت افزودن این کلاس به فایل
//! dll
//! استفاده میشود
class PHONEBOOKLIBRARYSHARED_EXPORT ContactDetail
{
    friend class ContactDB;
public:
    ContactDetail();
    ContactDetail(const QString& _name,const QString& _phone,const QString& _email,const QString& _address);
    virtual ~ContactDetail();

    QString     getName() const;
    void        setName(const QString &name);

    QString     getPhone() const;
    void        setPhone(const QString &phone);

    QString     getEmail() const;
    void        setEmail(const QString &email);

    QString     getAddress() const;
    void        setAddress(const QString &address);

    int         getID() const;

protected:
    int     mID;        // آی دی منحصر به فرد برای هر آیتم
    QString mName;      // نام مخاطب
    QString mPhone;     // شماره تلفن مخاطب
    QString mEmail;     // ایمیل مخاطب
    QString mAddress;   // آدرس مخاطب
};

#endif // CONTACTDETAIL_H
