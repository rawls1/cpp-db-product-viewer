#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Fl= 0;
    ui->label_4->setScaledContents(true);
    connect(ui->tableView,SIGNAL(customContextMenuRequested(QPoint)),SLOT(CustomMenuReq(QPoint)));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    cdlg = new ConnectionDialog();
    cdlg -> show();
}

void MainWindow::on_pushButton_clicked()
{
    qmodel = new QSqlQueryModel();

    qmodel-> setQuery("SELECT p.ID, p.Name AS [Наименование], c.catName, p.imagePath FROM product p INNER JOIN Categories c ON c.ID = p.catID"); //формируем запрос

    ui->tableView->setModel(qmodel);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(3);

    if (Fl == 0)
    {
        QSqlQuery *query = new QSqlQuery;
        query->exec("SELECT catName FROM Categories");

        while (query->next())
        {
            ui->comboBox->addItem(query->value(0).toString());
        }
    }

    Fl=1;
}

QString img;

void MainWindow::on_pushButton_2_clicked()
{
    adlg = new AddDialog();
    adlg->show();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int TempID;
    TempID = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();
    ui->lineEdit->setText(QString::number(TempID));

    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT Name, catID, imagePath FROM product WHERE ID=:ID");
    query->bindValue(":ID",TempID);
    query->exec();
    query->next();
    ui->lineEdit_2->setText(query->value(0).toString());
    ui->comboBox->setCurrentIndex(query->value(1).toInt() - 1);
    ui->label_4->setPixmap(query->value(2).toString());

}

void MainWindow::on_pushButton_4_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("DELETE FROM product WHERE ID=:ID");
    query->bindValue(":ID",ui->lineEdit->text());
    query->exec();

    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->comboBox->setCurrentIndex(0);

    MainWindow::on_pushButton_clicked();
}

void MainWindow::on_pushButton_3_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("UPDATE product SET Name=:Name, catID=:Category, imagePath = :img WHERE ID=:ID");
    query->bindValue(":ID",ui->lineEdit->text());
    query->bindValue(":Name",ui->lineEdit_2->text());
    query->bindValue(":Category",ui->comboBox->currentIndex() + 1);
    query->bindValue(":img", img);
    query->exec();

    MainWindow::on_pushButton_clicked();
}

// код для тщелчка правой кнопкой

void MainWindow::CustomMenuReq(QPoint pos)
{
    if (Fl==1)
    {
        QModelIndex index = ui->tableView->indexAt(pos);
        GlobID = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt(); // отслеживание положения курсора
        QMenu *menu = new QMenu(this); //создание контейнера меню
        QAction *ModRec = new QAction("Изменить...", this);
        QAction *DelRec = new QAction("Удалить", this);

        connect(DelRec, SIGNAL(triggered()),this, SLOT(DelRecAction())); // у слота и сигнала одинак параметры
        connect(ModRec, SIGNAL(triggered()),this, SLOT(ModRecAction()));

        menu->addAction(ModRec);

        menu->addAction(DelRec);

        menu->popup(ui->tableView->viewport()->mapToGlobal(pos));

    }
}

void MainWindow::DelRecAction()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("DELETE FROM product WHERE ID=:ID");
    query->bindValue(":ID",GlobID);

    query->exec();

    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->comboBox->setCurrentIndex(0);
    ui->label_4->setText("");

    MainWindow::on_pushButton_clicked();
}

void MainWindow::ModRecAction()
{
    mdlg = new ModifyDialog();
    connect(this, SIGNAL(sendID(int)),mdlg,SLOT(sendingID(int)));
    emit sendID(GlobID);//
    mdlg->show();
    disconnect(this, SIGNAL(sendID(int)),mdlg,SLOT(sendingID(int)));
}


void MainWindow::on_action_Wor_triggered()
{
    pdlg = new printDialog();
    pdlg->show();
}

void MainWindow::on_action_PDF_triggered()
{
    QString str;

    str.append("<html><head></head><body><center>"+QString("Пример простого отчёта"));
    str.append("<table border=1>");
    str.append("<tr>");
    str.append("<td>"+QString("ID")+"</td>");
    str.append("<td>"+QString("Наименование")+"</td>");
    str.append("<td>"+QString("Категория")+"</td>");
    str.append("</tr>");

    QSqlQuery *query = new QSqlQuery();
    query->exec("SELECT * FROM product");
    while (query->next())
    {
        str.append("<tr>");
        str.append("<td>"+QString(query->value(0).toString())+"</td>");
        str.append("<td>"+QString(query->value(1).toString())+"</td>");
        str.append("<td>"+QString(query->value(2).toString())+"</td>");
        str.append("</tr>");
    }

    str.append("</table></center></body></html>");

    QPrinter printer;
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);

    QString path = QFileDialog::getSaveFileName(NULL, "Сохранить", "Простой отчёт", "PDF(*.pdf)");

    if (path.isEmpty()) return;
    printer.setOutputFileName(path);

    QTextDocument doc;
    doc.setHtml(str);
    doc.print(&printer);

}

void MainWindow::on_toolButton_clicked()
{
    img = QFileDialog::getOpenFileName(0, "Выберите файл", img, "*.jpg");
    ui->label_4->setPixmap(img);
}
