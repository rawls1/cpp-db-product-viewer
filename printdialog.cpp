#include "printdialog.h"
#include "ui_printdialog.h"

printDialog::printDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::printDialog)
{
    ui->setupUi(this);
}

printDialog::~printDialog()
{
    delete ui;
}

void printDialog::on_toolButton_clicked()
{
    ui->lineEdit->setText(QFileDialog::getOpenFileName(0,"Выберите файл",".\\", "*.html"));
}

void printDialog::on_pushButton_clicked()
{
    QFile *file = new QFile();
    file->setFileName(ui->lineEdit->text());
    file->open(QIODevice::WriteOnly);

    QTextStream in(file);

    in << "<html><head></head><body><center>"+QString("Пример простого отчёта");
    in << "<table border=1>";
    in << "<tr>";
    in << "<td>"+QString("ID")+"</td>";
    in << "<td>"+QString("Наименование")+"</td>";
    in << "<td>"+QString("Категория")+"</td>";
    in << "</tr>";

    QSqlQuery *query = new QSqlQuery();
    query->exec("SELECT * FROM product");
    while (query->next())
    {
        in << "<tr>";
        in << "<td>"+QString(query->value(0).toString())+"</td>";
        in << "<td>"+QString(query->value(1).toString())+"</td>";
        in << "<td>"+QString(query->value(2).toString())+"</td>";
        in << "</tr>";
    }

    in << "</table></center></body></html>";

    file->close();

    QAxObject *word = new QAxObject("Word.Application",this);
    word->setProperty("DispalyAlerts",false);
    word->setProperty("Visible",true);
    QAxObject *doc = word->querySubObject("Documents");
    doc->dynamicCall("Open(QVariant)", ui->lineEdit->text());

}
