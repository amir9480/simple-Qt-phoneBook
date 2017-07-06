#include "contactmodel.h"

ContactModel::ContactModel()
{
    is_searching=false;
}

ContactModel::~ContactModel()
{

}

void ContactModel::do_search(QString _val)
{
    mSearchResult.clear();
    // جستجو رو انجام میدیم و نتیجه توی متغیر مد نظر میریزیم
    mSearchResult=mDB.findContact(_val);
}

int ContactModel::rowCount(const QModelIndex &) const
{
    // اگه در حال سرچ باشیم سایز نتیجه جستجو رو بر میگردونیم وگرنه تعداد کل اجزا رو بر میگردونیم
    if(is_searching)
        return mSearchResult.size();
    return mDB.countAll();
}

int ContactModel::columnCount(const QModelIndex &) const
{
    return 5;
}

QVariant ContactModel::data(const QModelIndex &index, int role) const
{
    // تعیین جهت متن
    if(role==Qt::TextAlignmentRole)
    {
        switch(index.column())
        {
        // آدرس و نام راست چین هستند
        case 0:case 3:
            return Qt::AlignRight;
        case 1:case 2:case 4:
            return Qt::AlignLeft;
        }
    }
    // نمایش محتویات
    if(role==Qt::DisplayRole)
    {
        ContactDetail cd;
        // اگه در حال سرچ هستیم محتویات رو از داخل نتایج جستجو میخونیم وگرنه از کل محتویات انتخاب میکنیم
        if(is_searching)
            cd=mSearchResult[index.row()];
        else
            cd=mDB.getContactAtIndex(index.row());

        switch(index.column())
        {
        case 0:
            return cd.getAddress();
        case 1:
            return cd.getEmail();
        case 2:
            return cd.getPhone();
        case 3:
            return cd.getName();
        case 4:
            return cd.getID();
        }
    }
    return QVariant();
}

QVariant ContactModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role==Qt::DisplayRole&&orientation==Qt::Horizontal)
    {
        switch(section)
        {
        case 0:
            return QStringLiteral("آدرس");
        case 1:
            return QStringLiteral("ایمیل");
        case 2:
            return QStringLiteral("تلفن");
        case 3:
            return QStringLiteral("نام");
        case 4:
            return QStringLiteral("ID");
        }
    }
    return QVariant();
}

ContactDB &ContactModel::getDB()
{
    return mDB;
}

bool ContactModel::getIs_searching() const
{
    return is_searching;
}

void ContactModel::setIs_searching(bool value)
{
    if(value==false)
        mSearchResult.clear();
    is_searching = value;
}
