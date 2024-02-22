#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connectiondialog.h"
#include "ui_connectiondialog.h"
#include <QSqlQueryModel>
#include "adddialog.h"
#include "ui_adddialog.h"
#include "modifydialog.h"
#include "ui_modifydialog.h"
#include "printdialog.h"
#include "ui_printdialog.h"
#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void CustomMenuReq(QPoint pos);

    void DelRecAction();

    void ModRecAction();

    void on_action_Wor_triggered();

    void on_action_PDF_triggered();

    void on_toolButton_clicked();

signals:
    void sendID(int);

private:
    Ui::MainWindow *ui;
    ConnectionDialog *cdlg;
    AddDialog *adlg;
    ModifyDialog *mdlg;
    QSqlQueryModel *qmodel;
    printDialog *pdlg;

    int Fl;
    int GlobID;
};
#endif // MAINWINDOW_H
