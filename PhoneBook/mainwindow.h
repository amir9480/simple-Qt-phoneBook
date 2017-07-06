#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "contactdb.h"

#include <QtCore>
#include <QtWidgets>

#include "contactmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // برای مدیریت کردن دستی یه سری رویداد ها
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    // اسلات نمایش منوی راست کلیک روی جدول
    void on_tableView_customContextMenuRequested(const QPoint &pos);

    // اضافه کردن یک مخاطب جدید
    void on_action_add_triggered();

    // اصلاح مخاطب انتخاب  شده
    void on_action_edit_triggered();

    // حزف مخاطب انتخاب شده
    void on_action_delete_triggered();

    // کلیک روی دکمه ی جستجو
    void on_search();

    // دوبار کلیک کردن روی سطر جدول
    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    ContactModel* tableModel;

    QLineEdit*  ui_searchBox;
    QPushButton* ui_searchbutton;
};

#endif // MAINWINDOW_H
