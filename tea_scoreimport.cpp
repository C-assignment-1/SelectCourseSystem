#include "tea_scoreimport.h"
#include "ui_tea_scoreimport.h"
#include "QFile"
#include "QTextStream"
#include "QStringList"
#include "QDebug"
#include "QMessageBox"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>


tea_scoreimport::tea_scoreimport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tea_scoreimport)
{
    ui->setupUi(this);

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
                            int i=0;
                            while(sql_query.next())
                            {
                                QString subject=sql_query.value(3).toString();
                                this->model->setHorizontalHeaderItem(i,new QStandardItem(subject));
                                this->ui->tableView->setColumnWidth(i,80);
                                ui->cbb_sortway->addItem("按"+subject+"分数查询");
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
    this->ui->tableView->setModel(model);

//    if(readfile()==-1)
//    {
//        this->close();
//        QMessageBox::critical(this,"错误","文件读取失败","确认");
//    }
}

tea_scoreimport::tea_scoreimport(QWidget *parent,QString cname):
    QDialog(parent),
    ui(new Ui::tea_scoreimport)
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
                            int i=0;
                            while(sql_query.next())
                            {
                                QString subject=sql_query.value(1).toString();
                                this->model->setHorizontalHeaderItem(i,new QStandardItem(subject));
                                this->ui->tableView->setColumnWidth(i,80);
                                ui->cbb_sortway->addItem(subject);
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
    this->ui->tableView->setModel(model);
}

tea_scoreimport::~tea_scoreimport()
{
    delete ui;
}

void tea_scoreimport::reset()
{
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
                            int i=0;
                            while(sql_query.next())
                            {
                                QString subject=sql_query.value(3).toString();
                                this->model->setHorizontalHeaderItem(i,new QStandardItem(subject));
                                this->ui->tableView->setColumnWidth(i,80);
                                ui->cbb_sortway->addItem(subject);
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
}

int tea_scoreimport::readfile()
{
    score_line.clear();
    QFile file("score.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return -1;
    }
    QTextStream in(&file);
    int row=0;
    while (!in.atEnd())
    {
        QString line=in.readLine();
        score_line.append(line);
        QStringList subs=line.split(" ");
        for(int i=0;i<subs.length();i++)
        {
           this->model->setItem(row,i,new QStandardItem(subs.at(i)));
        }
        row++;
    }
    file.close();
    return 0;
}

void tea_scoreimport::on_btn_dosort_clicked()
{
    this->model->clear();
    reset();

    QString type=ui->cbb_sortway->currentText();
    qDebug()<<type;

    //执行搜寻：知道flag，得到科目名字，搜寻成绩，排序

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
//        QSqlQuery sql_query;
//        QString select_sql= QString("selcet * from Bscore where courseName ='%1'").arg(type);
//        if(!sql_query.exec())
//        {
//            qDebug() << sql_query.lastError();
//        }
//        else
//        {
            QSqlQuery sql_query;
            QString select_max_sql = QString("select * from Bscore order by score and where courseName ='%1'").arg(type);
            QString studentName;
            QString score = 0;

            sql_query.prepare(select_max_sql);
            if(!sql_query.exec())
            {
                qDebug() << sql_query.lastError();
            }
            else
            {
                int counter=0;
                while(sql_query.next())
                {
                    studentName=sql_query.value(0).toString();
                    score = sql_query.value(2).toString();
                    this->model->setHorizontalHeaderItem(0,new QStandardItem("姓名"));
                    this->model->setHorizontalHeaderItem(1,new QStandardItem("成绩"));
                    QStandardItem *item = new QStandardItem(studentName);
                    model->setItem(counter,0,item);
                    item = new QStandardItem(score);
                    model->setItem(counter,1,item);
                    //QStandardItem *item = new QStandardItem(score);
                    //model->setItem(0,col,item);
                    qDebug() << QString("score:%1").arg(score);
                    counter++;
                }
            }
        //}
        ui->tableView->setModel(model);
    }
    database.close();

//    readfile();
//    int flag=this->ui->cbb_sortway->currentIndex();
//    switch (flag) {
//    case 0:
//        model->sort(6,Qt::DescendingOrder);
//        break;
//    case 1:
//        model->sort(3,Qt::DescendingOrder);
//        break;
//    case 2:
//        model->sort(4,Qt::DescendingOrder);
//        break;
//    case 3:
//        model->sort(5,Qt::DescendingOrder);
//        break;
//    case 4:
//        model->sort(1,Qt::AscendingOrder);
//        break;
//    case 5:
//        model->sort(2,Qt::AscendingOrder);
//        break;
//    default:
//        break;
//    }
}

void tea_scoreimport::on_btn_analyse_clicked()
{
    this->model->clear();
    reset();

    int sum=0;
    int numberOfStudent=0;
    int average=0;
    int numberOfPass=0;
    float rateOfPass=0;

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
        QString select_max_sql = "select * from Bscore order by score";
        int score = 0;

        sql_query.prepare(select_max_sql);
        if(!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            while(sql_query.next())
            {
                score=sql_query.value(2).toInt();
                sum=sum+score;
                numberOfStudent++;
                average=sum/numberOfStudent;
                this->model->setHorizontalHeaderItem(0,new QStandardItem("平均分"));
                this->ui->tableView->setColumnWidth(0,80);
                this->model->setItem(0,0,new QStandardItem(average));
            }
        }

        select_max_sql = "select * from Bscore where score >= 60";
        sql_query.prepare(select_max_sql);
        if(!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            while(sql_query.next())
            {
                numberOfPass++;
            }
            rateOfPass=numberOfPass/numberOfStudent;
            this->model->setHorizontalHeaderItem(1,new QStandardItem("及格率"));
            this->ui->tableView->setColumnWidth(0,80);
            this->model->setItem(0,0,new QStandardItem(rateOfPass));
        }
    }
    database.close();

//    readfile();
//    on_btn_dosort_clicked();
//    double sum_math=0,sum_eng=0,sum_phy=0,sum=0;
//    double pass_math=0,pass_eng=0,pass_phy=0;
//    double ave_math=0,ave_eng=0,ave_phy=0,ave_sum=0;
//    double var_math=0,var_eng=0,var_phy=0,var_sum=0;
//    int row=this->model->rowCount();
//    for(int i=0;i<row;i++)//计算数学总分和通过人数
//    {
//        QModelIndex index=model->index(i,3,QModelIndex());
//        QString temp= index.data().toString();
//        double one=temp.toDouble();
//        sum_math+=one;
//        if(one>=60)
//        {
//            pass_math++;
//        }
//    }
//    for(int i=0;i<row;i++)//计算英语总分和通过人数
//    {
//        QModelIndex index=model->index(i,4,QModelIndex());
//        QString temp= index.data().toString();
//        double one=temp.toDouble();
//        sum_eng+=one;
//        if(one>=60)
//        {
//            pass_eng++;
//        }
//    }
//    for(int i=0;i<row;i++)//计算物理总分和通过人数
//    {
//        QModelIndex index=model->index(i,5,QModelIndex());
//        QString temp= index.data().toString();
//        double one=temp.toDouble();
//        sum_phy+=one;
//        if(one>=60)
//        {
//            pass_phy++;
//        }
//    }
//    for(int i=0;i<row;i++)//计算总分和
//    {
//        QModelIndex index=model->index(i,6,QModelIndex());
//        QString temp= index.data().toString();
//        double one=temp.toDouble();
//        sum+=one;
//    }

//    pass_math/=row;pass_eng/=row;pass_phy/=row;
//    ave_math=sum_math/row;ave_eng=sum_eng/row;ave_phy=sum_phy/row;ave_sum=sum/row;

//    for(int i=0;i<row;i++)
//    {
//        QModelIndex index=model->index(i,3,QModelIndex());
//        QString temp= index.data().toString();
//        double one=temp.toDouble();
//        var_math+=(one-ave_math)*(one-ave_math);
//    }
//    for(int i=0;i<row;i++)
//    {
//        QModelIndex index=model->index(i,4,QModelIndex());
//        QString temp= index.data().toString();
//        double one=temp.toDouble();
//        var_eng+=(one-ave_eng)*(one-ave_eng);
//    }
//    for(int i=0;i<row;i++)
//    {
//        QModelIndex index=model->index(i,5,QModelIndex());
//        QString temp= index.data().toString();
//        double one=temp.toDouble();
//        var_phy+=(one-ave_phy)*(one-ave_phy);
//    }
//    for(int i=0;i<row;i++)
//    {
//        QModelIndex index=model->index(i,6,QModelIndex());
//        QString temp= index.data().toString();
//        double one=temp.toDouble();
//        var_sum+=(one-ave_sum)*(one-ave_sum);
//    }

//    var_math/=row;var_eng/=row;var_phy/=row;var_sum/=row;

//    this->model->setItem(++row,0,new QStandardItem("及格率"));
//    this->model->setItem(row,3,new QStandardItem(QString::number(pass_math)));
//    this->model->setItem(row,4,new QStandardItem(QString::number(pass_eng)));
//    this->model->setItem(row,5,new QStandardItem(QString::number(pass_phy)));
//    this->model->setItem(++row,0,new QStandardItem("平均分"));
//    this->model->setItem(row,3,new QStandardItem(QString::number(ave_math)));
//    this->model->setItem(row,4,new QStandardItem(QString::number(ave_eng)));
//    this->model->setItem(row,5,new QStandardItem(QString::number(ave_phy)));
//    this->model->setItem(row,6,new QStandardItem(QString::number(ave_sum)));
//    this->model->setItem(++row,0,new QStandardItem("方差"));
//    this->model->setItem(row,3,new QStandardItem(QString::number(var_math)));
//    this->model->setItem(row,4,new QStandardItem(QString::number(var_eng)));
//    this->model->setItem(row,5,new QStandardItem(QString::number(var_phy)));
//    this->model->setItem(row,6,new QStandardItem(QString::number(var_sum)));
}

void tea_scoreimport::setSname(QString name)
{
    sname=name;
}

QString tea_scoreimport::getSname()
{
    return sname;
}
