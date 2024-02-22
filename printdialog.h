#ifndef PRINTDIALOG_H
#define PRINTDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QAxObject>


namespace Ui {
class printDialog;
}

class printDialog : public QDialog
{
    Q_OBJECT

public:
    explicit printDialog(QWidget *parent = nullptr);
    ~printDialog();

private slots:
    void on_toolButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::printDialog *ui;
};

#endif // PRINTDIALOG_H
