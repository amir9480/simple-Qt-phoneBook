#ifndef CONTACTDIALOG_H
#define CONTACTDIALOG_H

#include <QDialog>

namespace Ui {
class ContactDialog;
}

class ContactDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContactDialog(QWidget *parent = 0);
    ~ContactDialog();

    // تهیه محتویات فیلد خاص
    QString getName();
    QString getPhone();
    QString getEmail();
    QString getAddress();

    // تنظیم مقدار اولیه فیلد ها
    void    setFirstValue(QString _name,QString _phone,QString _email,QString _address);

    // آیا محتویات توی فرم تایید نشده
    bool getIs_canceled() const;

private slots:
    // اسلات کلیک روی دکمه لغو
    void on_button_cancel_2_clicked();

    // اسلات کلیک روی دکمه تایید
    void on_button_ok_clicked();

private:
    Ui::ContactDialog *ui;
    bool is_canceled;
};

#endif // CONTACTDIALOG_H
