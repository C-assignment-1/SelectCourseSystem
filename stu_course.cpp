#include "stu_course.h"
#include "ui_stu_course.h"
#include "QFile"
#include "QTextStream"
#include "QMessageBox"
#include "QDebug"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "student.h"


float sum;

stu_course::stu_course(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stu_course)
{
    ui->setupUi(this);


    qDebug()<<sname;

    this->model1=new QStandardItemModel;

    this->model1->setHorizontalHeaderItem(0,new QStandardItem("课程名称"));
    this->model1->setHorizontalHeaderItem(1,new QStandardItem("课程编号"));
    this->model1->setHorizontalHeaderItem(2,new QStandardItem("课程性质"));
    this->model1->setHorizontalHeaderItem(3,new QStandardItem("学分"));
    this->model1->setHorizontalHeaderItem(4,new QStandardItem("开课学院"));
    this->model1->setHorizontalHeaderItem(5,new QStandardItem("上课地点"));

    this->ui->tb_course->setModel(model1);

    this->ui->tb_course->setColumnWidth(0,120);
    this->ui->tb_course->setColumnWidth(1,80);
    this->ui->tb_course->setColumnWidth(2,100);
    this->ui->tb_course->setColumnWidth(3,50);
    this->ui->tb_course->setColumnWidth(4,90);
    this->ui->tb_course->setColumnWidth(5,90);

    this->ui->tb_course->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tb_course->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->model2=new QStandardItemModel;

    this->model2->setHorizontalHeaderItem(0,new QStandardItem("课程名称"));
    this->model2->setHorizontalHeaderItem(1,new QStandardItem("课程编号"));
    this->model2->setHorizontalHeaderItem(2,new QStandardItem("课程性质"));
    this->model2->setHorizontalHeaderItem(3,new QStandardItem("学分"));
    this->model2->setHorizontalHeaderItem(4,new QStandardItem("开课学院"));
    this->model2->setHorizontalHeaderItem(5,new QStandardItem("上课地点"));

    this->ui->tb_select->setModel(model2);

    this->ui->tb_select->setColumnWidth(0,120);
    this->ui->tb_select->setColumnWidth(1,80);
    this->ui->tb_select->setColumnWidth(2,100);
    this->ui->tb_select->setColumnWidth(3,50);
    this->ui->tb_select->setColumnWidth(4,90);
    this->ui->tb_select->setColumnWidth(5,90);

    this->ui->tb_select->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tb_select->setEditTriggers(QAbstractItemView::NoEditTriggers);

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
        QSqlQuery sql_query;
        QString select_all_sql = "select * from Acourse";
        sql_query.prepare(select_all_sql);
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            int counter=0;
            while(sql_query.next())
            {
                QString id = sql_query.value(0).toString();
                QString name = sql_query.value(1).toString();
                QString property = sql_query.value(2).toString();
                QString credit = sql_query.value(3).toString();
                QString college = sql_query.value(4).toString();
                QString address = sql_query.value(5).toString();
                qDebug()<<name<<id<<property<<credit<<college<<address;
                QStandardItem *item = new QStandardItem(name);
                model1->setItem(counter,0,item);
                item = new QStandardItem(id);
                model1->setItem(counter,1,item);
                item = new QStandardItem(property);
                model1->setItem(counter,2,item);
                item = new QStandardItem(credit);
                model1->setItem(counter,3,item);
                item = new QStandardItem(college);
                model1->setItem(counter,4,item);
                item = new QStandardItem(address);
                model1->setItem(counter,5,item);
                //id int primary key, name varchar(30), property varchar(30), credit int, college varchar(30), address varchar(30)
                counter++;
            }

            ui->tb_course->setModel(model1);
            //ui->tb_course->show();

        }
        database.close();
        qDebug()<<"finish model1";



//    if(readcoursefile()==-1)
//    {
//        this->close();
//        QMessageBox::critical(this,"错误","文件读取失败，无法进行查找","确认");
//    }

//    if(readselectedfile()==-1)
//    {
//        this->close();
//        QMessageBox::critical(this,"错误","文件读取失败，无法进行查找","确认");
//    }

//    int r=0;
//    for(int i=0;i<selected_line.length();i++)
//    {
//        QString line=selected_line.at(i);
//        line=line.trimmed();
//        QStringList linesplit=line.split(" ");
//        display1(r++, linesplit);
//    }

//    this->ui->le_sum->setText(QString("%1").arg(sum));


}
}

stu_course::~stu_course()
{
    delete ui;
}

void stu_course::reset()
{
    this->model1->setHorizontalHeaderItem(0,new QStandardItem("课程名称"));
    this->model1->setHorizontalHeaderItem(1,new QStandardItem("课程编号"));
    this->model1->setHorizontalHeaderItem(2,new QStandardItem("课程性质"));
    this->model1->setHorizontalHeaderItem(3,new QStandardItem("学分"));
    this->model1->setHorizontalHeaderItem(4,new QStandardItem("开课学院"));
    this->model1->setHorizontalHeaderItem(5,new QStandardItem("上课地点"));

    this->ui->tb_course->setColumnWidth(0,120);
    this->ui->tb_course->setColumnWidth(1,80);
    this->ui->tb_course->setColumnWidth(2,100);
    this->ui->tb_course->setColumnWidth(3,50);
    this->ui->tb_course->setColumnWidth(4,90);
    this->ui->tb_course->setColumnWidth(5,90);
}

void stu_course::reset1()
{
    this->model2->setHorizontalHeaderItem(0,new QStandardItem("课程名称"));
    this->model2->setHorizontalHeaderItem(1,new QStandardItem("课程编号"));
    this->model2->setHorizontalHeaderItem(2,new QStandardItem("课程性质"));
    this->model2->setHorizontalHeaderItem(3,new QStandardItem("学分"));
    this->model2->setHorizontalHeaderItem(4,new QStandardItem("开课学院"));
    this->model2->setHorizontalHeaderItem(5,new QStandardItem("上课地点"));

    this->ui->tb_select->setColumnWidth(0,120);
    this->ui->tb_select->setColumnWidth(1,80);
    this->ui->tb_select->setColumnWidth(2,100);
    this->ui->tb_select->setColumnWidth(3,50);
    this->ui->tb_select->setColumnWidth(4,90);
    this->ui->tb_select->setColumnWidth(5,90);
}

int stu_course::readcoursefile()
{
    course_line.clear();
    QFile file("course.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return -1;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
       QString line=in.readLine();
       course_line.append(line);
    }
    file.close();
    return 0;
}

int stu_course::readselectedfile()
{
    sum=0;
    selected_line.clear();
    QFile file("selected.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return -1;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
       QString line=in.readLine();
       selected_line.append(line);
       QStringList linesplit=line.split(" ");
       sum+=linesplit.at(3).toFloat();
    }
    file.close();
    return 0;
}

void stu_course::display(int row, QStringList course_line)
{
    int i=0;
    for (i=0;i<course_line.length();i++)
    {
        this->model1->setItem(row,i,new QStandardItem(course_line.at(i)));
    }
}

void stu_course::display1(int row, QStringList selected_line)
{
    int i=0;
    for (i=0;i<selected_line.length();i++)
    {
        this->model2->setItem(row,i,new QStandardItem(selected_line.at(i)));
    }
}

void stu_course::on_btn_stu_doquery_clicked()
{
    this->model1->clear();
    reset();
    int flag=this->ui->cbb_queryway->currentIndex();
    QString cname=this->ui->le_cname->text();
    QString type;


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
        if (cname.length()<1)
        {
            QMessageBox::critical(this,"错误","输入信息错误，请重试！","确认");
        }
        else
        {
            switch (flag)
            {
            case 0:type="courseName";break;
            case 1:type="courseId";break;
            case 2:type="credit";break;
            case 3:type="property";break;
            case 4:type="college";break;
            default:break;
            }
            QSqlQuery sql_query;
            QString select_all_sql=QString("select * from Acourse where %1='%2'").arg(type).arg(cname);
            sql_query.prepare(select_all_sql);
            if(!sql_query.exec())
            {//courseId int primary key, courseName varchar(30), property varchar(30), credit int, college varchar(30), address varchar(30)
                qDebug()<<sql_query.lastError();
            }
            else
            {

                int counter=0;
                while(sql_query.next())
                {
                    QString id = sql_query.value(0).toString();
                    QString name = sql_query.value(1).toString();
                    QString password = sql_query.value(2).toString();
                    QString college = sql_query.value(3).toString();
                    QString classnum = sql_query.value(4).toString();
                    QString age = sql_query.value(5).toString();
                    QStandardItem *item = new QStandardItem(name);
                    model1->setItem(counter,0,item);
                    item = new QStandardItem(id);
                    model1->setItem(counter,1,item);
                    item = new QStandardItem(password);
                    model1->setItem(counter,2,item);
                    item = new QStandardItem(college);
                    model1->setItem(counter,3,item);
                    item = new QStandardItem(classnum);
                    model1->setItem(counter,4,item);
                    item = new QStandardItem(age);
                    model1->setItem(counter,5,item);
                    counter++;
                }

                ui->tb_course->setModel(model1);
                ui->tb_course->show();



//        int i=0,row=0;
//        for (i=0;i<course_line.length();i++)
//        {
//            QString line=course_line.at(i);
//            line=line.trimmed();
//            QStringList linesplit=line.split(" ");
//            switch (flag)
//            {
//            case 0:
//                if(linesplit.at(0).contains(cname,Qt::CaseSensitive))
//                {
//                    display(row++, linesplit);
//                }
//                break;
//            case 1:
//                if(linesplit.at(1).contains(cname,Qt::CaseSensitive))
//                {
//                    display(row++, linesplit);
//                }
//                break;
//            case 2:
//                if(linesplit.at(3).contains(cname,Qt::CaseSensitive))
//                {
//                    display(row++, linesplit);
//                }
//                break;
//            case 3:
//                if(linesplit.at(2).contains(cname,Qt::CaseSensitive))
//                {
//                    display(row++, linesplit);
//                }
//                break;
//            case 4:
//                if(linesplit.at(4).contains(cname,Qt::CaseSensitive))
//                {
//                    display(row++, linesplit);
//                }
//                break;
//            default:
//                break;
//            }
//        }
            }
        }
    }
    database.close();
}

void stu_course::writeIn(QString info)
{
    QFile mFile("selected.txt");
    if(!mFile.open(QIODevice::Append|QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","文件打开失败，课程没有添加","确认");
        return;
    }
    QTextStream out(&mFile);
    out<<info<<"\n";
    mFile.flush();
    mFile.close();
}

void stu_course::on_tb_course_doubleClicked(const QModelIndex &index)
{
    int flag=0;
    int row=this->ui->tb_course->currentIndex().row();
    QString name=model1->data(model1->index(row,0)).toString();
    QString id=model1->data(model1->index(row,1)).toString();
    qDebug()<<id;
    QString nature=model1->data(model1->index(row,2)).toString();
    QString point=model1->data(model1->index(row,3)).toString();
    QString college=model1->data(model1->index(row,4)).toString();
    QString place=model1->data(model1->index(row,5)).toString();
    int counter=0;

    //readselectedfile();
//    for(int i=0;i<selected_line.length();i++)
//    {
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
            QString select_all_sql = QString("select * from Cstudent where name='%1'").arg(sname);//"select * from Acourse where %1='%2'"
            sql_query.prepare(select_all_sql);
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {   
                int x=6;
                qDebug()<<sql_query.next();
//                while(sql_query.next())
//                {
                    qDebug()<<sql_query.value(6).toString()<<sql_query.value(7).toString()<<sql_query.value(8).toInt()<<id;
                    while(x<14)//没进来
                    {
                        if(sql_query.value(x).toString()==id)
                        {
                            QMessageBox::critical(this,"错误","不可重复选择课程！","确认");
                            flag=1;
                            break;
                        }
                        x++;
                    }
//                }
                qDebug()<<flag;
            }

        }
        database.close();
    //}

    if(flag==0)
    {
    QString messagebox_out="课程名称："+name+"\n"+"课程编号："+id+"\n"+"课程性质："+nature+"\n"+
                           "课程学分："+point+"\n"+"开课学院："+college+"\n"+"上课地点："+place;
    QString info=name+" "+id+" "+nature+" "+point+" "+college+" "+place;

    int id=model1->data(model1->index(row,1)).toInt();
    qDebug()<<id;

    int ret=QMessageBox::question(this,"请确认",messagebox_out,"选课","取消");
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
            QSqlQuery sql_query;
            QString select_all_sql = QString("select * from Cstudent where name='%1'").arg(sname);
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
                      if(sql_query.value(x).toString()=="")
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

            QString type;
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

            QString update_sql = QString("UPDATE  Cstudent  SET %1 = ?").arg(type);
            qDebug()<<QString("UPDATE  Cstudent  SET %1 = ?").arg(type);
            sql_query.prepare(update_sql);
            //"insert into Cstudent (id, name, password, college, classnum, age) values (?, ?, ?, ?, ?, ?)"
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
          //writeIn(info);
       }
    this->model2->clear();
    reset1();
    //readselectedfile();
    int r=0;
    for(int i=0;i<selected_line.length();i++)
    {
        QString line=selected_line.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split(" ");
        display1(r++, linesplit);
    }
    this->ui->le_sum->setText(QString("%1").arg(sum));
    }
}

void stu_course::on_tb_select_doubleClicked(const QModelIndex &index)
{
    int row=this->ui->tb_select->currentIndex().row();
    int id=model2->data(model2->index(row,1)).toInt();
    qDebug()<<id;
    int ret=QMessageBox::question(this,"请确认","确定退出当前课程？","退课","取消");
    if(ret==0)
    {
        int counter=0;
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
            QString select_all_sql = QString("select * from Cstudent where name='%1'").arg(sname);
            sql_query.prepare(select_all_sql);
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
              int x=6;
                qDebug()<<sql_query.next();
//              while(sql_query.next())
//              {
                  while(x<14)
                  {
                      qDebug()<<"enter1";
                      qDebug()<<sql_query.value(x).toString();
                      if(sql_query.value(x).toInt()==id)
                      {
                          qDebug()<<"enter2";
                          counter=x;
                          break;
                      }
                      x++;
                  }
//              }
            }
            counter=counter-5;
            qDebug()<<counter;

            QString type;
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

            QString update_sql = QString("UPDATE  Cstudent  SET %1 = 0").arg(type);
            qDebug()<<QString("UPDATE  Cstudent  SET %1 = ?").arg(type);
            sql_query.prepare(update_sql);
            //"insert into Cstudent (id, name, password, college, classnum, age) values (?, ?, ?, ?, ?, ?)"

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
//        int i=0;
//        for (i=0;i<selected_line.length();i++)
//        {
//            QString line=selected_line.at(i);
//            line=line.trimmed();
//            QStringList linesplit=line.split(" ");
//            if(name!=linesplit.at(0))
//            {
//                QFile file("selected_temp.txt");
//                if(!file.open(QIODevice::Append|QIODevice::Text))
//                {
//                   QMessageBox::critical(this,"错误","文件打开失败！","确认");
//                   return;
//                }
//            QTextStream out(&file);
//            out<<line+"\n";
//            file.close();
//            }
//        }
//        QFile file_old("selected.txt");
//        QFile file_new("selected_temp.txt");
//        if (file_old.exists())
//        {
//           file_old.remove();
//           file_new.rename("selected.txt");
//        }
//        else
//        {
//           QMessageBox::critical(this,"错误","未有信息保存为文件，无法退课","确认");
//        }
//        QMessageBox::information(this,"通知","退课成功！","确认");
    }
    this->model2->clear();
    reset1();
    readselectedfile();
    int r=0;
    for(int i=0;i<selected_line.length();i++)
    {
        QString line=selected_line.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split(" ");
        display1(r++, linesplit);
    }
    this->ui->le_sum->setText(QString("%1").arg(sum));
}

void stu_course::on_pushButton_clicked()
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
        // do something
        //操控数据库
        QSqlQuery sql_query;
        QString select_all_sql = "select * from Acourse";
        sql_query.prepare(select_all_sql);
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            int counter=0;
            while(sql_query.next())
            {
                QString id = sql_query.value(0).toString();
                QString name = sql_query.value(1).toString();
                QString password = sql_query.value(2).toString();
                QString college = sql_query.value(3).toString();
                QString classnum = sql_query.value(4).toString();
                QString age = sql_query.value(5).toString();
                QStandardItem *item = new QStandardItem(name);
                model1->setItem(counter,0,item);
                item = new QStandardItem(id);
                model1->setItem(counter,1,item);
                item = new QStandardItem(password);
                model1->setItem(counter,2,item);
                item = new QStandardItem(college);
                model1->setItem(counter,3,item);
                item = new QStandardItem(classnum);
                model1->setItem(counter,4,item);
                item = new QStandardItem(age);
                model1->setItem(counter,5,item);
                counter++;
            }

            ui->tb_course->setModel(model1);
            ui->tb_course->show();

        }
    }

    database.close();
//    this->model1->clear();
//    reset();
//    readcoursefile();
//    int r=0;
//    for(int i=0;i<course_line.length();i++)
//    {
//        QString line=course_line.at(i);
//        line=line.trimmed();
//        QStringList linesplit=line.split(" ");
//        display(r++, linesplit);
//    }
}

void stu_course::setSname(QString name)
{
    sname=name;
}

QString stu_course::getSname()
{
    return sname;
}

//int stu_course::function(int courseId)
//{
//    if(courseId==0)
//    {
//        return 0;
//    }

//    else
//    {
//        return 1;
//    }
//}



void stu_course::on_pushButton_2_clicked()
{
    this->model2->clear();
    reset1();
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
        QSqlQuery sql_query;
        QString select_all_sql = QString("select * from Cstudent where name='%1'").arg(sname);
        qDebug()<<sname;
        sql_query.prepare(select_all_sql);
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            qDebug()<<"enter first else";
            qDebug()<<sql_query.next();
//            while(sql_query.next())
//            {
                qDebug()<<sql_query.value(3).toString()<<sql_query.value(4).toString();
                qDebug()<<"enter sql_next be parpared enter while to get courseId";
//                QString courseIdOne = sql_query.value(6).toString();
//                QString courseIdTwo = sql_query.value(7).toString();
//                QString courseIdThree = sql_query.value(8).toString();
//                QString courseIdFour = sql_query.value(9).toString();
//                QString courseIdFive = sql_query.value(10).toString();
//                QString courseIdSix = sql_query.value(11).toString();
//                QString courseIdSeven = sql_query.value(12).toString();
//                QString courseIdEight = sql_query.value(13).toString();
                //qDebug()<<name<<id<<property<<credit<<college<<address;
                int i=1;
                int counter=0;
                while(i<=8)
                {
                    int courseId=sql_query.value(i+5).toInt();

                    qDebug()<<"courseId is "<<courseId;
//                    QString type="unknow";
//                    switch(i)
//                    {
//                    case 1:type=courseIdOne;break;
//                    case 2:type=courseIdTwo;break;
//                    case 3:type=courseIdThree;break;
//                    case 4:type=courseIdFour;break;
//                    case 5:type=courseIdFive;break;
//                    case 6:type=courseIdSix;break;
//                    case 7:type=courseIdSeven;break;
//                    case 8:type=courseIdEight;break;
//                    default: qDebug()<<"error";break;
//                    }
                    if(courseId!=0)
                    {
                        qDebug()<<"courseId!=0,enter if statement";


                        QSqlQuery sql_query;
                        QString select_all_sql = QString("select * from Acourse where courseId=%1").arg(courseId);
                        //QString select_all_sql=QString("select * from Acourse where %1='%2'").arg(type).arg(cname);
                        qDebug()<<QString("select * from Acourse where id='%1'").arg(courseId);
                        sql_query.prepare(select_all_sql);
                        if(!sql_query.exec())
                        {
                            qDebug()<<sql_query.lastError();
                        }
                        else
                        {
                              qDebug()<<"select information";
                            while(sql_query.next())
                            {   qDebug()<<"start select infromation of course";
                                QString id = sql_query.value(0).toString();
                                QString name = sql_query.value(1).toString();
                                QString property = sql_query.value(2).toString();
                                QString credit = sql_query.value(3).toString();
                                QString college = sql_query.value(4).toString();
                                QString address = sql_query.value(5).toString();
                                qDebug()<<name<<id<<property<<credit<<college<<address;
                                QStandardItem *item = new QStandardItem(name);
                                model2->setItem(counter,0,item);
                                item = new QStandardItem(id);
                                model2->setItem(counter,1,item);
                                item = new QStandardItem(property);
                                model2->setItem(counter,2,item);
                                item = new QStandardItem(credit);
                                model2->setItem(counter,3,item);
                                item = new QStandardItem(college);
                                model2->setItem(counter,4,item);
                                item = new QStandardItem(address);
                                model2->setItem(counter,5,item);

                                //id int primary key, name varchar(30), property varchar(30), credit int, college varchar(30), address varchar(30)
                                counter++;
                            }
                        }


                    }
                    i++;
                }

                //id int primary key, name varchar(30), property varchar(30), credit int, college varchar(30), address varchar(30)
//            }


            ui->tb_select->setModel(model2);
            ui->tb_select->show();
        }
    }

database.close();
}
