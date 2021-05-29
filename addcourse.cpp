#include "addcourse.h"
#include "ui_addcourse.h"
#include "QString"
#include "QDebug"
#include "QMessageBox"
#include "QFile"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QDebug>

addcourse::addcourse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addcourse)
{
    ui->setupUi(this);
}

addcourse::~addcourse()
{
    delete ui;
}

void addcourse::on_btn_sys_addcou_clicked()
{
    QString name=this->ui->le_course_name->text();
    QString id=this->ui->le_course_id->text();
    QString nature=this->ui->cbb_nature->currentText();
    QString point=this->ui->cbb_point->currentText();
    QString college=this->ui->cbb_college->currentText();
    QString place=this->ui->le_course_place->text();
    QString teacherName = ui->le_teacher_name->text();
    QString messagebox_out="课程名称："+name+"\n"+"课程编号："+id+"\n"+"课程性质："+nature+"\n"+"课程学分："+point+"\n"
                           +"开课学院："+college+"\n"+"上课地点："+place;
    QString info=name+" "+id+" "+nature+" "+point+" "+college+" "+place;

    bool charge=name.length()<1||id.length()<1||place.length()<1&id!=0;

//    QSqlDatabase database;
//    if (QSqlDatabase::contains("qt_sql_default_connection"))
//    {
//        database = QSqlDatabase::database("qt_sql_default_connection");
//    }
//    else
//    {
//        database = QSqlDatabase::addDatabase("QSQLITE");
//        database.setDatabaseName("MyDataBase.db");
//        database.setUserName("XingYeZhiXia");
//        database.setPassword("123456");
//    }

//    if (!database.open())
//    {
//        qDebug() << "Error: Failed to connect database." << database.lastError();
//    }
//    else
//    {
//        QSqlQuery sql_query;
//        QString select_all_sql = QString("select * from Cteacher where name='%1'").arg(teacherName);

//        sql_query.prepare(select_all_sql);
//        if(!sql_query.exec())
//        {
//            qDebug()<<sql_query.lastError();
//        }
//        else
//        {

//            if(sql_query.next())
//            {

//            }
//            else
//            {
//                QMessageBox::critical(this,"错误","请填写系统内已录入信息的老师","确定");
//            }
//        }
//    }
//    database.close();

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
               // do something
               //操控数据库
               //创建表
               QSqlQuery sql_query;
               QString insert_sql = "insert into Bcourse values (?, ?, ?, ?, ?, ?, ?)";
               sql_query.prepare(insert_sql);
               QString name = ui->le_course_name->text();
               int id = ui->le_course_id->text().toInt();
               QString property=this->ui->cbb_nature->currentText();
               int credit =this->ui->cbb_point->currentText().toInt();
               QString college=this->ui->cbb_college->currentText();
               QString address=this->ui->le_course_place->text();
               QString teacherName = ui->le_teacher_name->text();
               qDebug()<<name<<id<<property<<credit<<college<<address;
               sql_query.addBindValue(id);
               sql_query.addBindValue(name);
               sql_query.addBindValue(property);
               sql_query.addBindValue(credit);
               sql_query.addBindValue(college);
               sql_query.addBindValue(address);
               sql_query.addBindValue(teacherName);
               //id int primary key, name varchar(30), property varchar(30), credit int, college varchar(30), address
               //n,i,n,c,c,a
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


           QString type="unknow";
           int counter=0;
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
               QString select_all_sql = QString("select * from Cteacher where name='%1'").arg(teacherName);
               sql_query.prepare(select_all_sql);
               if(!sql_query.exec())
               {
                   qDebug()<<sql_query.lastError();
               }
               else
               {
                 int x=6;
                 qDebug()<<sql_query.next();
                 qDebug()<<sql_query.value(6).toString()<<sql_query.value(7).toString()<<sql_query.value(8).toString()<<sql_query.value(9).toString();
   //              while(sql_query.next())
   //              {//没进来
                     qDebug()<<"enter";
                     while(x<14)
                     {
                         qDebug()<<sql_query.value(8).toString();
                         if(sql_query.value(x).toInt()==0)
                         {
                             qDebug()<<"yes";
                             counter=x;
                             break;
                         }
                         x++;
                     }
   //              }
               }
               counter=counter-5;
               qDebug()<<counter;

               switch(counter)
               {
                   case 1: type="courseIdOne";break;
                   case 2: type="courseIdTwo";break;
                   case 3: type="courseIdThree";break;
                   case 4: type="courseIdFour";break;
                   case 5: type="courseIdFive";break;
                   case 6: type="courseIdSix";break;
                   case 7: type="courseIdSeven";break;
                   case 8: type="courseIdEight";break;
                   default:qDebug()<<"conunter errors";
               }
               qDebug()<<type;

               QString insert_sql = QString("update Cteacher  set %1 = ?").arg(type);
               //QString update_sql = QString("UPDATE  Cstudent  SET %1 = ?").arg(type);
               sql_query.prepare(insert_sql);
               int id = ui->le_course_id->text().toInt();
               sql_query.addBindValue(id);

               //query.exec("UPDATE  new_students  SET score = 100 , name = '小A'");
               //QString("insert into Cstudent (%1) values (?)").arg(type);
               //修改score和name所在的列内容
               if(!sql_query.exec())
               {
                   qDebug() << sql_query.lastError();
               }
               else
               {
                   qDebug() << "update successfully!";
               }

           }
           database.close();
          }
    }
}

//void addcourse::writeIn(QString info)
//{
//    this->ui->le_course_name->clear();
//    this->ui->le_course_id->clear();
//    this->ui->le_course_place->clear();
//    this->ui->le_course_name->setFocus();

//    QFile mFile("course.txt");
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

void addcourse::on_btn_sys_addcoucancel_clicked()
{
    this->close();
}
