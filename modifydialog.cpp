#include "modifydialog.h"
#include "ui_modifydialog.h"
#include <QSqlQuery>

    int tempID;

ModifyDialog::ModifyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyDialog)
{
    ui->setupUi(this);
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT Name,Category FROM product WHERE ID=:ID");
    query->bindValue(":ID",tempID);
    query->exec();
    query->next();
    ui->lineEdit->setText(query->value(0).toString());
    ui->lineEdit_2->setText(query->value(1).toString());
}

ModifyDialog::~ModifyDialog()
{
    delete ui;
}

void ModifyDialog::on_pushButton_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("UPDATE product SET Name=:Name, Category=:Category WHERE ID=:ID");
    query->bindValue(":ID",tempID);
    query->bindValue(":Name",ui->lineEdit->text());
    query->bindValue(":Category",ui->lineEdit_2->text());
    query->exec();

    if (query->exec())
    {
        close();
    }
}

void ModifyDialog::sendingID(int ID)
{
    tempID = ID;
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT Name,Category FROM product WHERE ID=:ID");
    query->bindValue(":ID",tempID);
    query->exec();
    query->next();
    ui->lineEdit->setText(query->value(0).toString());
    ui->lineEdit_2->setText(query->value(1).toString());
}
