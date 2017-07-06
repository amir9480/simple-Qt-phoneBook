#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "contactdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    tableModel(new ContactModel)
{
    ui->setupUi(this);

    // تنظیم مدل
    ui->tableView->setModel(tableModel);
    // ستون پنجم حاوی آی دی هست و نیازی به نمایشش نیست
    ui->tableView->hideColumn(4);
    // سایز ستون ها بر اساس محتویات تنظیم میشن
    ui->tableView->resizeColumnsToContents();
    // آخرین ستون همواره چسبیده باشه به انتهای جدول و فضای خالی باقی نمونه
    ui->tableView->horizontalHeader()->setStretchLastSection(false);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);


    ui_searchBox=new QLineEdit(this);
    ui_searchBox->setPlaceholderText(QStringLiteral("جستجو"));
    ui_searchbutton=new QPushButton(QStringLiteral("جستجو"),this);
    // نمیتونیم از دیزاینر فیلد و دکمه سرچ رو اضافه کنیم به تولباکس
    // پس به صورت دستی تعریفش میکنیم
    ui->toolBar->addWidget(ui_searchBox);
    ui->toolBar->addWidget(ui_searchbutton);

    connect(ui_searchbutton,SIGNAL(clicked(bool)),this,SLOT(on_search()));

    // مشخص میکنیم که فیلد جستجو رویداد هاش رو اول به این کلاس بفرسته
    // تابع
    // eventFilter
    ui_searchBox->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tableModel;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    // اگه نوع رویداد فشردن کلیک باشه
    if(event->type()==QEvent::KeyPress)
    {
        // کلید فشرده شده رو مشخص میکنیم
        switch (dynamic_cast<QKeyEvent*>(event)->key())
        {
        // اگه دکمه ای که فشرده شد اینتر بود جستجو انجام بشه
        case Qt::Key_Enter:case Qt::Key_Return:
            on_search();
            return true;
            break;
        default:
            break;
        }
    }
    return QMainWindow::eventFilter(watched,event);
}

void MainWindow::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    QMenu m;
    m.addAction(ui->action_add);
    m.addAction(ui->action_edit);
    m.addAction(ui->action_delete);
    m.exec(mapToGlobal(pos));

}

void MainWindow::on_action_add_triggered()
{
    ContactDialog d;
    d.setWindowTitle(QStringLiteral("افزودن مخاطب جدید"));
    d.exec();
    if(d.getIs_canceled()==false)
    {
        ContactDetail cd;
        cd.setName(d.getName());
        cd.setEmail(d.getEmail());
        cd.setPhone(d.getPhone());
        cd.setAddress(d.getAddress());
        tableModel->getDB().addContact(cd);
    }
    // محتویات جدول رو با عوض کردن مدل به روز میکنیم
    ui->tableView->setModel(nullptr);
    ui->tableView->setModel(tableModel);
    ui->tableView->hideColumn(4);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(false);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::on_action_edit_triggered()
{
    if(ui->tableView->selectionModel()->selectedRows().size()==0)
    {
        QMessageBox::warning(this,QStringLiteral("اخطار"),QStringLiteral("شما هیچ گزینه ای را جهت اصلاح انتخاب نکردید"),QMessageBox::Ok);
        return;
    }
    // ستونی که روش کلیک شده
    int sid=ui->tableView->selectionModel()->selectedRows()[0].row();
    // آی دی آیتم انتخاب شده رو از طریق محتویات ستون مخفی تهیه میکنیم
    int _sid=ui->tableView->model()->data(ui->tableView->model()->index(sid,4)).toInt();

    ContactDialog d;
    ContactDetail cd=tableModel->getDB().getContact(_sid);
    d.setWindowTitle(QStringLiteral("اصلاح مشخصات مخاطب"));
    d.setFirstValue(cd.getName(),cd.getPhone(),cd.getEmail(),cd.getAddress());
    d.exec();
    if(d.getIs_canceled()==false)
    {
        cd.setName(d.getName());
        cd.setEmail(d.getEmail());
        cd.setPhone(d.getPhone());
        cd.setAddress(d.getAddress());
        tableModel->getDB().updateContact(_sid,cd);

        if(tableModel->getIs_searching())
            tableModel->do_search(ui_searchBox->text());
    }
    ui->tableView->setModel(nullptr);
    ui->tableView->setModel(tableModel);
    ui->tableView->hideColumn(4);
    ui->tableView->selectRow(sid);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(false);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::on_action_delete_triggered()
{
    if(ui->tableView->selectionModel()->selectedRows().size()==0)
    {
        QMessageBox::warning(this,QStringLiteral("اخطار"),QStringLiteral("شما هیچ گزینه ای را جهت اصلاح انتخاب نکردید"),QMessageBox::Ok);
        return;
    }
    int sid=ui->tableView->selectionModel()->selectedRows()[0].row();
    int _sid=ui->tableView->model()->data(ui->tableView->model()->index(sid,4)).toInt();

    if(QMessageBox::warning(this,QStringLiteral("اخطار"),QStringLiteral("برای حزف مخاطب مطمئن هستید؟"),QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes)
        tableModel->getDB().removeContact(_sid);

    if(tableModel->getIs_searching())
        tableModel->do_search(ui_searchBox->text());

    ui->tableView->setModel(nullptr);
    ui->tableView->setModel(tableModel);
    ui->tableView->hideColumn(4);
    ui->tableView->selectRow(sid);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(false);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::on_search()
{
    if(tableModel->getIs_searching())
    {
        // اگه در حال جستجو بود با کلیک روی دکمه محتویات جدول به حالت عادی برمیگرده
        tableModel->setIs_searching(false);
        ui_searchbutton->setText(QStringLiteral("جستجو"));
    }
    else
    {
        // اگه در حال سرچ نباشیم پس سرچ رو شروع میکنیم
        tableModel->setIs_searching(true);
        tableModel->do_search(ui_searchBox->text());
        ui_searchbutton->setText(QStringLiteral("بازگشت به حالت عادی"));
    }
    ui->tableView->setModel(nullptr);
    ui->tableView->setModel(tableModel);
    ui->tableView->hideColumn(4);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(false);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &)
{
    on_action_edit_triggered();
}
