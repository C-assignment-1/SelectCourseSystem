#include "addstu.h"
#include "ui_addstu.h"
#include "QString"
#include "QDebug"
#include "QMessageBox"
#include "QFile"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QDebug>
#include<QPushButton>
#include<QLineEdit>

addstu::addstu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addstu)
{
    ui->setupUi(this);
}

addstu::~addstu()
{
    delete ui;
}

void addstu::on_btn_sys_addstu_clicked()
{
    QString name = ui->le_stu_name->text();
    int id = ui->le_stu_id->text().toInt();
    int password=this->ui->le_stu_password->text().toInt();
    QString college=this->ui->cbb_stu->currentText();
    QString classnum=this->ui->le_stu_class->text();
    QString age=this->ui->le_stu_age->text();

    QSqlDatabase database;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
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
        
        //操控数据库
        //创建表
        QSqlQuery sql_query;

    //插入数据

        QString insert_sql = "insert into Cstudent (id, name, password, college, classnum, age) values (?, ?, ?, ?, ?, ?)";
        sql_query.prepare(insert_sql);


    //            m_timer=new QTimer;
    //            connect(m_timer,SIGNAL(timeout()),this,SLOT(print()));
    //            m_timer->start(1000);

        //QString text = ui->textEdit->toPlainText();

    //            int buf_OUT[65];
    //                QString sendStr = ui->textEdit->toPlainText();
    //                for(int i = 0;i < sendStr.length();++i){
    //                    QChar t = sendStr.at(i);
    //                    buf_OUT[i] = t.toLatin1()-'0';
    //                }

    //                for(int i = 0;i < sendStr.length();++i)
    //                {
    //                    cout<<buf_OUT[i];
    //                }


        //    QString name=this->ui->le_stu_name->text();
        //    QString id=this->ui->le_stu_id->text();
        //    QString password=this->ui->le_stu_password->text();
        //    QString college=this->ui->cbb_stu->currentText();
        //    QString classnum=this->ui->le_stu_class->text();
        //    QString age=this->ui->le_stu_age->text();

        sql_query.addBindValue(id);
        sql_query.addBindValue(name);
        sql_query.addBindValue(password);
        sql_query.addBindValue(college);
        sql_query.addBindValue(classnum);
        sql_query.addBindValue(age);
        if(!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            qDebug() << "inserted successfully!";
        }
//    if(!sql_query.exec("INSERT INTO student VALUES(4, \"Li\", 23)"))
//    {
//        qDebug() << sql_query.lastError();
//    }
//    else
//    {
//        qDebug() << "inserted Li!";
//    }


    }
    database.close();
//    QString name=this->ui->le_stu_name->text();
//    QString id=this->ui->le_stu_id->text();
//    QString password=this->ui->le_stu_password->text();
//    QString college=this->ui->cbb_stu->currentText();
//    QString classnum=this->ui->le_stu_class->text();
//    QString age=this->ui->le_stu_age->text();
//    QString messagebox_out="姓名："+name+"\n"+"学号："+id+"\n"+"密码："+password+"\n"+
//                           "院系："+college+"\n"+"班级："+classnum+"\n"+"年龄："+age;
//    QString info=name+" "+id+" "+password+" "+college+" "+classnum+" "+age;

//    bool charge=name.length()<1||id.length()<9||password.length()<6||
//                classnum.length()<6||id.at(0)!="s";

//    if(charge==1)
//    {
//        QMessageBox::critical(this,"错误","信息填写不完整，请检查","确定");
//    }
//    else
//    {
//       int ret=QMessageBox::question(this,"请确认",messagebox_out,"确认","取消");
//       if(ret==0)
//          {
//             writeIn(info);
//          }
//    }
}

//void addstu::writeIn(QString info)
//{
//    this->ui->le_stu_name->clear();
//    this->ui->le_stu_id->clear();
//    this->ui->le_stu_password->clear();
//    this->ui->le_stu_class->clear();
//    this->ui->le_stu_age->clear();
//    this->ui->le_stu_name->setFocus();

//    QFile mFile("student.txt");
//    if(!mFile.open(QIODevice::Append|QIODevice::Text))
//    {
//        QMessageBox::critical(this,"错误","文件打开失败，信息没有写入","确认");
//        return;
//    }
//    QTextStream out(&mFile);
//    out<<info<<"\n";
//    mFile.flush();
//    mFile.close();
//}

void addstu::on_btn_sys_addstu_cancel_clicked()
{
    this->close();
}
