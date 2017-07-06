#include "contactdialog.h"
#include "ui_contactdialog.h"

ContactDialog::ContactDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContactDialog)
{
    ui->setupUi(this);
    is_canceled=true;

    // از بین بردن علامت سوال روی فرم ما
    setWindowFlags(windowFlags()&~(Qt::WindowContextHelpButtonHint));
    // تنظیم میکنیم که فیلد تلفن فقط بتونه عدد دریافت کنه
    // 9 : عدد
    // # : علامت مثبت / منفی / عدد
    ui->phone->setInputMask("#999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999");
}

ContactDialog::~ContactDialog()
{
    delete ui;
}

QString ContactDialog::getName()
{
    return ui->name->text();
}

QString ContactDialog::getPhone()
{
    return ui->phone->text();
}

QString ContactDialog::getEmail()
{
    return ui->email->text();
}

QString ContactDialog::getAddress()
{
    return ui->address->text();
}

void ContactDialog::setFirstValue(QString _name, QString _phone, QString _email, QString _address)
{
    ui->name->setText(_name);
    ui->email->setText(_email);
    ui->phone->setText(_phone);
    ui->address->setText(_address);
}

bool ContactDialog::getIs_canceled() const
{
    return is_canceled;
}

void ContactDialog::on_button_cancel_2_clicked()
{
    close();
}

void ContactDialog::on_button_ok_clicked()
{
    // یعنی محتویات فرم تایید شده هست
    is_canceled=false;
    close();
}
