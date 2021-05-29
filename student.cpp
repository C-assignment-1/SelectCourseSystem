#include "student.h"
#include "ui_student.h"
#include "mainwindow.h"
#include "QDebug"
#include "QFile"
#include "QMessageBox"
#include "stu_course.h"
#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

student::student(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::student)
{
    ui->setupUi(this);
    sname="unknow";
    qDebug()<<getSname();

//    if(readfile()==-1)
//    {
//        this->close();
//        QMessageBox::critical(this,"错误","文件读取失败，无法进行查找","确认");
//    }
}

student::~student()
{
    delete ui;
}

int student::readfile()
{
    QFile file("score.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return -1;
    }
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line=in.readLine();
            score_line.append(line);
        }
    file.close();
    return 0;
}

void student::on_btn_stu_query_clicked()
{
//    for(int i=0;i<score_line.length();i++)
//    {
//        QString line=score_line.at(i);
//        line=line.trimmed();
//        QStringList linesplit=line.split(" ");
//        if(account==linesplit.at(1))
//        {
//        QString messagebox_out="姓名："+linesplit.at(0)+"\n"+"学号："+linesplit.at(1)+"\n"
//                               +"班级："+linesplit.at(2)+"\n"+"数学："+linesplit.at(3)+"\n"
//                               +"英语："+linesplit.at(4)+"\n"+"物理："+linesplit.at(5)+"\n"
//                               +"总分："+linesplit.at(6)+"\n";
//        QMessageBox::information(this,"成绩显示",messagebox_out,"确认","取消");
//        }
//    }
    QString messagebox_out="姓名"+sname+"\n";
    QSqlDatabase database;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");//如果需要使用自定义的名称则要添加第二个参数database = QSqlDatabase::addDatabase("QSQLITE", "my_sql_connection");
        database.setDatabaseName("MyDataBase.db");
        database.setUserName("XingYeZhiXia");
        database.setPassword("123456");
    }

    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        // do something
        //操控数据库
        QSqlQuery sql_query;
        qDebug()<<sname;
        QString select_all_sql = QString("select * from score where studentName='%1'").arg(sname);//"select * from Acourse where %1='%2'"
        sql_query.prepare(select_all_sql);
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            while(sql_query.next())
            {
                QString subject=sql_query.value(2).toString();
                QString subjectName=sql_query.value(3).toString();
                messagebox_out=messagebox_out+subjectName+subject+"\n";
            }
        }
    }
    database.close();

    QMessageBox::information(this,"成绩显示",messagebox_out,"确认","取消");
}

void student::on_btn_stu_select_clicked()
{
    qDebug()<<sname;
    stu_course a;
    a.setSname(sname);
    a.exec();
}

void student::on_pushButton_clicked()
{
    this->close();
}

void student::on_btn_return_clicked()
{
    this->close();
    MainWindow *main_window=new MainWindow;
    main_window->show();
}

void student::setSname(QString name)
{
    sname=name;
}

QString student::getSname()
{
    return sname;
}
