#include "contactdetail.h"


ContactDetail::ContactDetail()
{
}

ContactDetail::ContactDetail(const QString &_name, const QString &_phone, const QString &_email, const QString &_address):
    mID(-1),
    mName(_name),
    mPhone(_phone),
    mEmail(_email),
    mAddress(_address)
{

}

ContactDetail::~ContactDetail()
{

}

QString ContactDetail::getName() const
{
    return mName;
}

void ContactDetail::setName(const QString &name)
{
    mName = name;
}

QString ContactDetail::getPhone() const
{
    return mPhone;
}

void ContactDetail::setPhone(const QString &phone)
{
    mPhone = phone;
}

QString ContactDetail::getEmail() const
{
    return mEmail;
}

void ContactDetail::setEmail(const QString &email)
{
    mEmail = email;
}

QString ContactDetail::getAddress() const
{
    return mAddress;
}

void ContactDetail::setAddress(const QString &address)
{
    mAddress = address;
}

int ContactDetail::getID() const
{
    return mID;
}
