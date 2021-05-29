#include "addtea.h"
#include "ui_addtea.h"
#include "QMessageBox"
#include "QFile"
#include "QTextStream"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QDebug>

addtea::addtea(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addtea)
{
    ui->setupUi(this);
}

addtea::~addtea()
{
    delete ui;
}

void addtea::on_btn_sys_addtea_clicked()
{
    QString name=this->ui->le_tea_name->text();
    QString id=this->ui->le_tea_id->text();
    QString password=this->ui->le_tea_password->text();
    QString sex=this->ui->cbb_sex->currentText();
    QString age=this->ui->le_tea_age->text();
    QString college=this->ui->cbb_tea->currentText();
    QString messagebox_out="姓名："+name+"\n"+"工号："+id+"\n"+"密码："+password+"\n"+
                           "性别："+sex+"\n"+"年龄："+age+"\n"+"院系："+college;
    QString info=name+" "+id+" "+password+" "+sex+" "+age+" "+college;

    bool charge=name.length()<1||id.length()<9||password.length()<6;

    if(charge==1)
    {
        QMessageBox::critical(this,"错误","信息填写不完整，请检查","确定");
    }
    else
    {
       int ret=QMessageBox::question(this,"请确认",messagebox_out,"确认","取消");
       if(ret==0)
          {
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
               QSqlQuery sql_query;
               QString insert_sql = "insert into Cteacher (id, name, password, college, gender, age) values (?, ?, ?, ?, ?, ?)";
               sql_query.prepare(insert_sql);

               sql_query.addBindValue(id);
               sql_query.addBindValue(name);
               sql_query.addBindValue(password);
               sql_query.addBindValue(college);
               sql_query.addBindValue(sex);
               sql_query.addBindValue(age);
               //id int primary key, name varchar(30), password int, gender varchar(30), classnum int, age int
               if(!sql_query.exec())
               {
                   qDebug() << sql_query.lastError();
               }
               else
               {
                   qDebug() << "inserted successfully!";
               }
           }
           database.close();

          }
    }
}

//void addtea::writeIn(QString info)
//{
//    this->ui->le_tea_name->clear();
//    this->ui->le_tea_id->clear();
//    this->ui->le_tea_password->clear();
//    this->ui->le_tea_age->clear();
//    this->ui->le_tea_name->setFocus();

//    QFile mFile("teacher.txt");
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

void addtea::on_btn_sys_addteacancel_clicked()
{
    this->close();
}
