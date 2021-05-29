#include "teacher.h"
#include "ui_teacher.h"
#include "tea_addscore.h"
#include "tea_scoreimport.h"
#include "tea_querystu.h"
#include "mainwindow.h"

teacher::teacher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::teacher)
{
    ui->setupUi(this);
}

teacher::~teacher()
{
    delete ui;
}

void teacher::on_btn_close_clicked()
{
    this->close();
}

void teacher::on_btn_tea_addscore_clicked()
{
    tea_addscore a(this,sname);
    //setSname(sname);
    a.exec();
}

void teacher::on_btn_tea_scoreInport_clicked()
{
    tea_scoreimport a(this,sname);
    //a.setSname(sname);
    a.exec();
}

void teacher::on_btn_tea_querystu_clicked()
{
    tea_querystu a(this,sname);
    a.exec();
}

void teacher::on_btn_return_clicked()
{
    this->close();
    MainWindow *main_window=new MainWindow;
    main_window->show();
}

void teacher::setSname(QString name)
{
    sname=name;
}

QString teacher::getSname()
{
    return sname;
}
