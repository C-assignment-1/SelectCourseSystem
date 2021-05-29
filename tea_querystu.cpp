#include "tea_querystu.h"
#include "ui_tea_querystu.h"
#include "QFile"
#include "QMessageBox"
#include "QTextStream"
#include "QDebug"
#include "changedata.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

QString name1;
QString id1;
QString classname1;
QString math1;
QString eng1;
QString phy1;
int i=1;
QString type="unknow";
QString courseIdOne="unknow";
QString courseIdTwo="unknow";
QString courseIdTHree="unknow";
QString courseIdFour="unknow";
QString courseIdFive="unknow";
QString courseIdSix="unknow";
QString courseIdSeven="unknow";
QString courseIdEight="unknow";

tea_querystu::tea_querystu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tea_querystu)
{
    ui->setupUi(this);
}

tea_querystu::tea_querystu(QWidget *parent,QString cname):
        QDialog(parent),
        ui(new Ui::tea_querystu)
{
    ui->setupUi(this);
    sname=cname;

    this->model=new QStandardItemModel;

    this->model->setHorizontalHeaderItem(0,new QStandardItem("姓名"));

    this->ui->tableView->setModel(model);

    this->ui->tableView->setColumnWidth(0,60);

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
                                switch(i)
                                {
                                case 0: courseIdOne = subject;break;
                                case 1: courseIdTwo = subject;break;
                                case 2: courseIdTHree = subject;break;
                                case 3: courseIdFour = subject;break;
                                case 4: courseIdFive = subject;break;
                                case 5: courseIdSix = subject;break;
                                case 6: courseIdSeven = subject;break;
                                case 7: courseIdEight = subject;break;
                                default: qDebug()<<"error";break;
                                }
                                this->model->setHorizontalHeaderItem(i,new QStandardItem(subject));
                                this->ui->tableView->setColumnWidth(i,80);
                                i++;
                            }
                        }
                    }

                    x++;
                }
            }
        }
    }
    database.close();
    qDebug()<<"i="<<i;
    this->ui->tableView->setModel(model);
//    int row=this->ui->tableView->currentIndex().row();
//    model->removeRow(row);
//    model->submit();

//    if(readfile()==-1)
//    {
//        this->close();
//        QMessageBox::critical(this,"错误","文件读取失败，无法进行查找","确认");
//    }
}

tea_querystu::~tea_querystu()
{
    delete ui;
}

void tea_querystu::reset()
{
    i=1;
    this->model->setHorizontalHeaderItem(0,new QStandardItem("姓名"));
    this->ui->tableView->setColumnWidth(0,60);

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
                                this->model->setHorizontalHeaderItem(i,new QStandardItem(subject));
                                this->ui->tableView->setColumnWidth(i,80);
                                i++;
                            }
                        }
                    }

                    x++;
                }
            }
        }
    }
    database.close();
    qDebug()<<"i="<<i;
}

int tea_querystu::readfile()
{
    score_line.clear();
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
//        qDebug()<<line;
    }
    file.close();
    return 0;
}

void tea_querystu::display(int row, QStringList score_line)
{
    int i=0;
    for (i=0;i<score_line.length();i++)
    {
        this->model->setItem(row,i,new QStandardItem(score_line.at(i)));
    }
}

void tea_querystu::on_btn_doquery_clicked()
{
    this->model->clear();
    reset();

    QString infor=this->ui->le_info->text();
    QStandardItem *item = new QStandardItem(infor);
    model->setItem(0,0,item);

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
        int col=1;
        QString subject;
        qDebug()<<"i="<<i;
        while(col<i)
        {
            switch(i)
            {
            case 1:subject=courseIdOne;break;
            case 2:subject=courseIdTwo;break;
            case 3:subject=courseIdTHree;break;
            case 4:subject=courseIdFour;break;
            case 5:subject=courseIdFive;break;
            case 6:subject=courseIdSix;break;
            case 7:subject=courseIdSeven;break;
            case 8:subject=courseIdEight;break;
            default: qDebug()<<"error";
            }

            //subject=model->data(model->index(0,col)).toString();
            qDebug()<<subject<<infor;
            QSqlQuery sql_query;
            qDebug()<<sname;
            QString select_all_sql = QString("select * from Bscore where studentName='%1' and courseName='%2'").arg(infor).arg(subject);
            sql_query.prepare(select_all_sql);
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                qDebug()<<sql_query.next();
//                while(sql_query.next())
//                {
                    qDebug()<<"enter next";
                    QString score = sql_query.value(2).toString();
                    qDebug()<<sql_query.value(2).toString();
                    QStandardItem *item = new QStandardItem(score);
                    model->setItem(0,col,item);                    
                    //id int primary key, name varchar(30), property varchar(30), credit int, college varchar(30), address varchar(30)
//                }
            }
            col++;
        }
        database.close();
   }
   this->ui->tableView->setModel(model);
//    readfile();
//    int flag=this->ui->cbb_querymode->currentIndex();
//    QString infor=this->ui->le_info->text();

//    if (infor.length()<1)
//    {
//            QMessageBox::critical(this,"错误","输入信息错误，请重试！","确认");
//    }
//    else
//    {
////            qDebug()<<flag;
//            int i=0,row=0;
//            for (i=0;i<score_line.length();i++)
//            {
//                QString line=score_line.at(i);
//                line=line.trimmed();
//                QStringList linesplit=line.split(" ");
//                switch (flag)
//                {
//                case 0:
//                    if(linesplit.at(0).contains(infor,Qt::CaseSensitive))
//                    {
//                        display(row++, linesplit);
////                        qDebug()<<1;
//                    }
//                    break;
//                case 1:
//                    if(linesplit.at(1).contains(infor,Qt::CaseSensitive))
//                    {
//                         display(row++, linesplit);
////                         qDebug()<<2;
//                    }
//                    break;
//                case 2:
//                    if(linesplit.at(2).contains(infor,Qt::CaseSensitive))
//                    {
//                         display(row++, linesplit);
////                         qDebug()<<3;
//                    }
//                break;
//                default:break;
//                }
//            }
//    }
}

void tea_querystu::on_tableView_doubleClicked(const QModelIndex &index)
{
    changedata a;
    int row=this->ui->tableView->currentIndex().row();
    name1=model->data(model->index(row,0)).toString();
    id1=model->data(model->index(row,1)).toString();
    classname1=model->data(model->index(row,2)).toString();
    math1=model->data(model->index(row,3)).toString();
    eng1=model->data(model->index(row,4)).toString();
    phy1=model->data(model->index(row,5)).toString();
//    sum1=model->data(model->index(row,6)).toString();
    a.exec();
}

void tea_querystu::setSname(QString name)
{
    sname=name;
}

QString tea_querystu::getSname()
{
    return sname;
}










