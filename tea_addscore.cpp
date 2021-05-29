#include "tea_addscore.h"
#include "ui_tea_addscore.h"
#include "QString"
#include "QFile"
#include "QTextStream"
#include "QMessageBox"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

tea_addscore::tea_addscore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tea_addscore)
{
    ui->setupUi(this);
    //qDebug()<<sname;
    qDebug()<<"start database";
    QSqlDatabase database;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        qDebug()<<"adddatabase";
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
        qDebug()<<"do something";
        // do something
        //操控数据库
        QSqlQuery sql_query;
        qDebug()<<sname;
        QString select_all_sql = QString("select * from Cteacher where name='%1'").arg(sname);//"select * from Acourse where %1='%2'"
        sql_query.prepare(select_all_sql);
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            //qDebug()<<sql_query.next();
            while(sql_query.next())
            {
                int x=6;
                while(x<14)
                {
                    int subjectId=sql_query.value(x).toInt();
                    if(subjectId!=0)
                    {
                        QSqlQuery sql_query;
                        QString select_all_sql = QString("select * from Bcourse where courseId='%1'").arg(subjectId);
                        sql_query.prepare(select_all_sql);
                        if(!sql_query.exec())
                        {
                            qDebug()<<sql_query.lastError();
                        }
                        else
                        {
                            while(sql_query.next())
                            {
                                QString subject=sql_query.value(1).toString();
                                ui->comboBox->addItem(subject);
                            }
                        }
                    }

                    x++;
                }
            }
        }
    }
    database.close();
}


//tea_addscore::tea_addscore(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::tea_addscore)
tea_addscore::tea_addscore(QWidget *parent,QString cname):
    QDialog(parent),
    ui(new Ui::tea_addscore)
{
    ui->setupUi(this);
    sname=cname;
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
        QString select_all_sql = QString("select * from Cteacher where name='%1'").arg(sname);//"select * from Acourse where %1='%2'"
        sql_query.prepare(select_all_sql);
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            qDebug()<<"start x";
            //qDebug()<<sql_query.next();
            while(sql_query.next())
            {qDebug()<<"enter next";
                int x=6;
                while(x<14)
                {qDebug()<<"enter x";
                    int subjectId=sql_query.value(x).toInt();
                    if(subjectId!=0)
                    {
                        qDebug()<<"enter subjectId";
                        QSqlQuery sql_query;
                        QString select_all_sql = QString("select * from Bcourse where courseId='%1'").arg(subjectId);
                        sql_query.prepare(select_all_sql);
                        if(!sql_query.exec())
                        {
                            qDebug()<<sql_query.lastError();
                        }
                        else
                        {
                            while(sql_query.next())
                            {
                                QString subject=sql_query.value(1).toString();
                                ui->comboBox->addItem(subject);
                            }
                        }
                    }
                    x++;
                }
            }
        }
    }
    database.close();
}

tea_addscore::~tea_addscore()
{
    delete ui;
}


void tea_addscore::on_btn_addscore_add_clicked()
{
    QString name=this->ui->le_addscore_name->text();
    QString score=this->ui->le_addscore_math->text();
    QString subject= ui->comboBox->currentText();

    QString messagebox_out="姓名："+name+"\n"+"总分："+score;
    QString information=name+" "+" "+score;

    bool charge=name.length()<1||score.length()<1;
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
               QString insert_sql = "insert into Bscore (studentName, teacherName, score, courseName) values (?, ?, ?, ?)";
               //(studentName, teacherName, score, courseName)
               sql_query.prepare(insert_sql);

               sql_query.addBindValue(name);
               sql_query.addBindValue(sname);
               sql_query.addBindValue(score);
               sql_query.addBindValue(subject);
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
             //writeIn(information);
          }
    }
}

//void tea_addscore::writeIn(QString information)
//{
//    this->ui->le_addscore_name->clear();
//    this->ui->le_addscore_id->clear();
//    this->ui->le_addscore_class->clear();
//    this->ui->le_addscore_math->clear();
//    this->ui->le_addscore_eng->clear();
//    this->ui->le_addscore_phy->clear();
//    this->ui->le_addscore_name->setFocus();
//    QFile mFile("score.txt");
//    if(!mFile.open(QIODevice::Append|QIODevice::Text))
//    {
//        QMessageBox::critical(this,"错误","文件打开失败，信息没有写入","确认");
//        return;
//    }
//    QTextStream out(&mFile);
//    out<<information<<"\n";
//    mFile.flush();
//    mFile.close();
//}

void tea_addscore::on_btn_addscore_cancel_clicked()
{
    this->close();
}

void tea_addscore::setSname(QString name)
{
    sname=name;
}

QString tea_addscore::getSname()
{
    return sname;
}
