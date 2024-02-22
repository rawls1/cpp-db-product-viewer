#include "connectiondialog.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setText(".\\SQLEXPRESS");
    ui->lineEdit_2->setText("productView");
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::on_pushButton_clicked()
{
    db = QSqlDatabase::addDatabase("QODBC"); // ДРАЙВЕР В ЭТОМ ИСТОЧНИКЕ
    db.setDatabaseName("DRIVER={SQL Server};SERVER="+ui->lineEdit->text()
                       +";DATABASE="+ui->lineEdit_2->text()+";");
    db.setUserName(ui->lineEdit_3->text());
    db.setPassword(ui->lineEdit_4->text());

    msg= new QMessageBox();

    if (db.open())
        msg->setText("подключение установленно");
    else
        msg->setText("подключение не установленно. причина:"+QSqlError(db.lastError()).text()); //текст ошибки
    msg->show();
}
