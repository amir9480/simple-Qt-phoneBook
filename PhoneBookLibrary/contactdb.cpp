#include "contactdb.h"

//! تابع آماده کردن دیتابیس مورد نظر
QSqlDatabase PHONEBOOKLIBRARYSHARED_EXPORT getDataBase()
{
    // به دلیل راحتی استفاده میکنیم SQLite از
    static QSqlDatabase sdb=QSqlDatabase::addDatabase("QSQLITE");
    // این مقدار وقتی این تابع حداقل یک بار فراخوانی شه تبدیل به صحیح میشه
    static bool is_ready=false;
    if(is_ready==false)
    {
        sdb.setHostName("localhost");
        sdb.setDatabaseName("phonebook");
        sdb.setUserName("root");
        sdb.setPassword("123456");
        // اگه باز نشد یعنی یه چیزی اشکال داره
        if(sdb.open()==false)
        {
            qDebug()<<"Can Not open SQLITE DataBase";
            Q_ASSERT(1);
        }
        // این تابع قبلا فراخوانی شده و دیتابیس حاضر هست
        is_ready=true;
    }
    return sdb;
}

ContactDB::ContactDB():
    mQuery(getDataBase())
{
    //! اگه جدول مورد نظر وجود نداشت اون رو درست میکنیم
    //!  رو برگردوند یعنی دستور اس کیو ال ما اشکال داره یا شایدم چیز دیگه ای false اگه تابع مقدار
    if(mQuery.exec("CREATE TABLE IF NOT EXISTS phonebook("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name varchar(255),"
                "phone varchar(255),"
                "email varchar(255),"
                "address varchar(512)"
                ");")==false)
        // برای شناسایی اشتباهمون استفاده میکنیم lastError از تابع
        qDebug()<<mQuery.lastError();
}

ContactDB::~ContactDB()
{

}

void ContactDB::addContact(const ContactDetail &_d)
{
    // اول یه بیس کلی از دستور آماده میکنیم
    mQuery.prepare("INSERT INTO phonebook(name,phone,email,address) VALUES (?,?,?,?)");
    // مقدار ها را درون دستور اس کیو ال قرار میدیم
    // محتویات تابع با ؟ عوض میشه
    mQuery.bindValue(0,_d.getName());
    mQuery.bindValue(1,_d.getPhone());
    mQuery.bindValue(2,_d.getEmail());
    mQuery.bindValue(3,_d.getAddress());
    if(mQuery.exec()==false)
        qDebug()<<mQuery.lastError();
}

int ContactDB::countAll()
{
    if(mQuery.exec("SELECT COUNT(id) FROM phonebook WHERE 1")==false)
        qDebug()<<mQuery.lastError();
    mQuery.next();
    return mQuery.value(0).toInt();
}

QList<ContactDetail> ContactDB::findContact(QString _val)
{
    QList<ContactDetail> o;
    // بر اساس نام / تلفن / ایمیل / آدرس  سرچ خواهد کرد
    if(mQuery.exec(QString("SELECT id,name,phone,email,address FROM phonebook WHERE name LIKE '%")+_val+"%' or phone LIKE '%"+_val+"%' or email LIKE '%"+_val+"%' or address LIKE '%"+_val+"%' ")==false)
        qDebug()<<mQuery.lastError();
    // تازمانی که سطر وجود داره به بعدی بریم
    while(mQuery.next())
    {
        ContactDetail cd;
        // برای دسترسی به محتویات سلول موجود در سطر استفاده میکنیم
        cd.mID=(mQuery.value(0).toInt());
        cd.setName(mQuery.value(1).toString());
        cd.setPhone(mQuery.value(2).toString());
        cd.setEmail(mQuery.value(3).toString());
        cd.setAddress(mQuery.value(4).toString());
        // محتویات خونده شده رو به بازگشتی تابع اضافه میکنیم
        o.push_back(cd);
    }
    return o;
}

QList<ContactDetail> ContactDB::getAll()
{
    QList<ContactDetail> o;
    if(mQuery.exec("SELECT id,name,phone,email,address FROM phonebook WHERE 1")==false)
        qDebug()<<mQuery.lastError();
    while(mQuery.next())
    {
        ContactDetail cd;
        cd.mID=(mQuery.value(0).toInt());
        cd.setName(mQuery.value(1).toString());
        cd.setPhone(mQuery.value(2).toString());
        cd.setEmail(mQuery.value(3).toString());
        cd.setAddress(mQuery.value(4).toString());
        o.push_back(cd);
    }
    return o;
}

ContactDetail ContactDB::getContact(int id)
{
    ContactDetail o;
    mQuery.prepare("SELECT id,name,phone,email,address FROM phonebook WHERE id = ?");
    mQuery.bindValue(0,id);
    if(mQuery.exec()==false)
        qDebug()<<mQuery.lastError();
    // اگه اشتباه بود یعنی اصلا مخاطبی با این مشخصات وجود نداره و مقدار پیش فرض بر میگردونه
    if(mQuery.next()==false)
        return o;
    o.mID=(mQuery.value(0).toInt());
    o.setName(mQuery.value(1).toString());
    o.setPhone(mQuery.value(2).toString());
    o.setEmail(mQuery.value(3).toString());
    o.setAddress(mQuery.value(4).toString());
    return o;
}

ContactDetail ContactDB::getContactAtIndex(int _index)
{
    ContactDetail o;
    mQuery.prepare("SELECT id,name,phone,email,address FROM phonebook LIMIT 1 OFFSET ?");
    mQuery.bindValue(0,_index);
    if(mQuery.exec()==false)
        qDebug()<<mQuery.lastError();
    if(mQuery.next()==false)
        return o;
    o.mID=(mQuery.value(0).toInt());
    o.setName(mQuery.value(1).toString());
    o.setPhone(mQuery.value(2).toString());
    o.setEmail(mQuery.value(3).toString());
    o.setAddress(mQuery.value(4).toString());
    return o;
}

void ContactDB::removeContact(int _id)
{
    mQuery.prepare("DELETE FROM phonebook WHERE id = ?");
    mQuery.bindValue(0,_id);
    if(mQuery.exec()==false)
        qDebug()<<mQuery.lastError();
}

void ContactDB::updateContact(int _id, const ContactDetail &_d)
{
    mQuery.prepare("UPDATE phonebook SET name= ? ,phone= ? ,email= ? ,address= ?  WHERE id = ?");
    mQuery.bindValue(0,_d.getName());
    mQuery.bindValue(1,_d.getPhone());
    mQuery.bindValue(2,_d.getEmail());
    mQuery.bindValue(3,_d.getAddress());
    mQuery.bindValue(4,_id);
    if(mQuery.exec()==false)
        qDebug()<<mQuery.lastError();
}


// این قسمت صرفا جهت تست کردن مستقیم این کتاب خانه هست

//int main()// just for testing
//{
//    ContactDB db;
//    //db.addContact(ContactDetail("reza","45678","reza@test","reza's address"));

//    QList<ContactDetail> a= db.getAll();
//    qDebug()<<a.size()<<"\n"<<db.countAll()<<"\n";
//    for(int i=0;i<a.size();i++)
//        qDebug()<<QString("%1 - %2 - %3 - %4 - %5")
//                  .arg(a[i].getID())
//                  .arg(a[i].getName())
//                  .arg(a[i].getPhone())
//                  .arg(a[i].getEmail())
//                  .arg(a[i].getAddress());


//    return 0;
//}

