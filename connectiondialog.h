#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QWidget *parent = nullptr);
    ~ConnectionDialog();


private slots:
    void on_pushButton_clicked();

private:
    Ui::ConnectionDialog *ui;
    QSqlDatabase db;
    QMessageBox *msg;
};

#endif // CONNECTIONDIALOG_H
