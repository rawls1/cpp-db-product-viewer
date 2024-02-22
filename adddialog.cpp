#include "adddialog.h"
#include "ui_adddialog.h"
#include <QFileDialog>

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);

    QSqlQuery *query = new QSqlQuery;
    query->exec("SELECT catName FROM Categories");

    while (query->next())
    {
        ui->comboBox->addItem(query->value(0).toString());
    }
}

AddDialog::~AddDialog()
{
    delete ui;
}

QString imgPath;

void AddDialog::on_pushButton_clicked()
{
    QSqlQuery *query = new QSqlQuery();

    query -> prepare("INSERT INTO product VALUES (:Name,:Category,:img)"); //заготовка для запроса
    query -> bindValue(":Name", ui->lineEdit ->text());
    query -> bindValue(":Category", ui->comboBox->currentIndex() + 1);
    query -> bindValue(":img",imgPath);

    if(query->exec())
        close(); //выполнение запроса

}

void AddDialog::on_toolButton_clicked()
{
    imgPath = QFileDialog::getOpenFileName(0, "Выберите файл", imgPath, "*.jpg");
    ui->label_3->setPixmap(imgPath);
}
