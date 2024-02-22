#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();

private slots:
    void on_pushButton_clicked();

    void on_toolButton_clicked();

private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
