#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "system.h"
#include "student.h"
#include "teacher.h"
#include "QFile"
#include "QTextStream"
#include "QMessageBox"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QDebug>
#include<QPushButton>
#include<QLineEdit>

QString account;
QString password;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
        //创建表
        QSqlQuery sql_query;

//        QSqlQuery query;

//            query.exec(QString("select count(*) from sqlite_master where type='table' and name='%1'").arg("student"));
//            if(query.next())
//            {
//                if(query.value(0).toInt()==0)
//                {
//                  qDebug()<<"exist";// 表不存在
//                }
//                else
//                {
//                    qDebug()<<"doesn't exist";//表存在
//                }

//            }

        QString create_student_sql = "create table Cstudent (id int primary key, name varchar(30), password int, college varchar(30), classnum int, age int, courseIdOne int, courseIdTwo int, courseIdThree int, courseIdFour int, courseIdFive int, courseIdSix int, courseIdSeven int, courseIdEight int)";
        QString create_teacher_sql = "create table Cteacher (id int primary key, name varchar(30), password int, college varchar(30), gender int, age int, courseIdOne int, courseIdTwo int, courseIdThree int, courseIdFour int, courseIdFive int, courseIdSix int, courseIdSeven int, courseIdEight int)";
        //QString create_controller_sql = "create table contorller (id int primary key, name varchar(30), password int, college varchar(30), classnum int, age int)";
        QString create_course_sql = "create table Acourse (courseId int primary key, courseName varchar(30), property varchar(30), credit int, college varchar(30), address varchar(30), teacherName varchar(30))";
       // QString create_score_sql = "create table Ascore (studentName varchar(30) primary key, teacherName varchar(30), score int, courseId int)";
        //name,id,classnum,subject_scores
        //获取学生选取的科目信息，tableview，双击，进入录入学生的成绩
        //QString connect_table_sql="select students.courseId,teacher.courseId, from course inner join students on course.courseId = students.courseId inner join teacher  on course.courseId =teacher.courseId";

//        if(sql_query.exec("ALTER TABLE  students ADD COLUMN address varchar(30)"))   //向 students表里添加新的一列,标题为classId,内容格式为VARCHAR
//        {//courseId int , courseName varchar(30), property varchar(30), credit int, collegeOfCourse varchar(30), address varchar(30)
//            qDebug()<<"add successfully";
//        }
//        else
//        {
//            qDebug() << "Error: Fail to add." << sql_query.lastError();
//        }

        //sql_query.exec("ALTER TABLE students RENAME TO new_students");      //将students重命名为new_students
        //sql_query.exec("UPDATE  new_students  SET score = 100 , name = '小A'");       //修改score和name所在的列内容
        //sql_query.exec("UPDATE  new_students  SET 结果='不合格'  WHERE  score<60 ");   //判断小于60的设为不合格,否则设为合格
        //sql_query.exec("UPDATE  new_students  SET 结果='合格'  WHERE  score>=60 ");
        sql_query.prepare(create_student_sql);
        if(!sql_query.exec())
        {
            qDebug() << "Error: Fail to create student table." << sql_query.lastError();
        }
        else
        {
            qDebug() << "Table created!";
        }
        sql_query.prepare(create_teacher_sql);
        if(!sql_query.exec())
        {
            qDebug() << "Error: Fail to create teacher table." << sql_query.lastError();
        }
        else
        {
            qDebug() << "Table created!";
        }
//        sql_query.prepare(create_controller_sql);
//        if(!sql_query.exec())
//        {
//            qDebug() << "Error: Fail to create controller table." << sql_query.lastError();
//        }
//        else
//        {
//            qDebug() << "Table created!";
//        }
        sql_query.prepare(create_course_sql);
        if(!sql_query.exec())
        {
            qDebug() << "Error: Fail to create course table." << sql_query.lastError();
        }
        else
        {
            qDebug() << "Table created!";
        }
//        sql_query.prepare(create_score_sql);
//        if(!sql_query.exec())
//        {
//            qDebug() << "Error: Fail to create score table." << sql_query.lastError();
//        }
//        else
//        {
//            qDebug() << "Table created!";
//        }

//        sql_query.prepare(connect_table_sql);
//        if(!sql_query.exec())
//        {
//            qDebug() << "Error: Fail to connect table." << sql_query.lastError();
//        }
//        else
//        {
//            qDebug() << "Table connected successfully!";
//        }

//        QString drop_all_table="drop table student";
//        sql_query.prepare(drop_all_table);
//        if(!sql_query.exec())
//        {
//            qDebug() << "Error: Fail to drop table." << sql_query.lastError();
//        }
//        else
//        {
//            qDebug() << "Table dropped successfully!";
//        }

    }
    database.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//int MainWindow::readstudentfile()
//{
//    QFile file("student.txt");
//    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
//    {
//        return -1;
//    }
//    QTextStream in(&file);
//    while (!in.atEnd())
//    {
//       QString line=in.readLine();
//       student_line.append(line);
//    }
//    file.close();
//    return 0;
//}

//int MainWindow::readteacherfile()
//{
//    QFile file("teacher.txt");
//    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
//    {
//        return -1;
//    }
//    QTextStream in(&file);
//    while (!in.atEnd())
//    {
//       QString line=in.readLine();
//       teacher_line.append(line);
//    }
//    file.close();
//    return 0;
//}

//int MainWindow::readcontroller()
//{
//    QFile file("controller.txt");
//    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
//    {
//        return -1;
//    }
//    QTextStream in(&file);
//    while (!in.atEnd())
//    {
//       QString line=in.readLine();
//       controller_line.append(line);
//    }
//    file.close();
//    return 0;
//}

void MainWindow::on_btn_denglu_clicked()
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
        int flag=0;
        QString cname=ui->le_zhanghao->text();
        qDebug()<<cname;
        int cpassword = ui->le_mima->text().toInt();
        qDebug()<<cpassword;



        if(cname==""&cpassword==0)
        {
            flag=1;
            QMessageBox::critical(this,"错误","请输入账号密码","确认");
        }

        if(flag==0)
        {
            QString type="unknown";
            int typeIndex=-1;
            typeIndex=ui->comboBox->currentIndex();
            int check=0;

            switch(typeIndex)
            {
                case 0:
                {
                QString select_all_sql = "select * from Cstudent";
                sql_query.prepare(select_all_sql);

                if(!sql_query.exec())
                {
                    qDebug()<<sql_query.lastError();
                }
                else
                {
                    while(sql_query.next())
                        {
                            int id = sql_query.value(0).toInt();
                            QString name = sql_query.value(1).toString();
                            int password = sql_query.value(2).toInt();
                            int courseId= sql_query.value(6).toInt();
                            qDebug()<<courseId;
                            qDebug()<<QString("id:%1    name:%2    password:%3").arg(id).arg(name).arg(password);
                            if(cname==name&cpassword==password)
                            {
                                check=1;
                                student a;
                                a.setSname(cname);
                                this->close();
                                a.exec();
                            }
                            else
                            {
                                qDebug()<<"error";

                            }

                        }

                }
                }
                break;
                case 1:
                {
                    QString select_all_sql = "select * from Cteacher";
                    sql_query.prepare(select_all_sql);

                    if(!sql_query.exec())
                    {
                        qDebug()<<sql_query.lastError();
                    }
                    else
                    {
                        while(sql_query.next())
                            {
                                int id = sql_query.value(0).toInt();
                                QString name = sql_query.value(1).toString();
                                int password = sql_query.value(2).toInt();
                                qDebug()<<QString("id:%1    name:%2    password:%3").arg(id).arg(name).arg(password);
                                if(cname==name&cpassword==password)
                                {
                                    check=1;
                                    teacher a;
                                    this->close();
                                    a.exec();
                                }
                                else
                                {
                                    qDebug()<<"error";

                                }

                            }

                     }
                }
                    break;
                case 2:
                {
                    if(cname=="controller"&cpassword==0000)
                    {
                        check=1;
                        class system a;
                        this->close();
                        a.exec();
                    }
                    else
                    {
                        qDebug()<<"error";

                    }
                }
                    break;
                default: qDebug()<<"error";
            }

        if(check!=1)
        {
            QMessageBox::critical(this,"错误","账号或密码错误\n（请检查账号类型）","确认");
        }

        }
    }
    database.close();



//    account=this->ui->le_zhanghao->text();
//    password=this->ui->le_mima->text();

//    if(readstudentfile()==-1)
//    {
//        this->close();
//        QMessageBox::critical(this,"错误","学生信息读取失败，\n学生账户无法登录，\n可登录管理员账户修改！","确认");
//    }
//    else if (readteacherfile()==-1)
//    {
//        this->close();
//        QMessageBox::critical(this,"错误","教师信息读取失败，\n教师账户无法登录，\n可登录管理员账户修改！","确认");
//    }

//    int i=0,j=0,flag=100;

//    if(account.at(0)=="s")
//    {
//    for (i=0;i<student_line.length();i++)
//    {
//        QString line=student_line.at(i);
//        line=line.trimmed();
//        QStringList linesplit=line.split(" ");
//        if(account==linesplit.at(1)&&password==linesplit.at(2))
//        {
//        flag=0;
//        }
//    }
//    }
//    else if(account.at(0)=="t")
//    {
//    for (j=0;j<teacher_line.length();j++) {
//        QString line=teacher_line.at(j);
//        line=line.trimmed();
//        QStringList linesplit=line.split(" ");
//        if(account==linesplit.at(1)&&password==linesplit.at(2))
//        {
//           flag=1;
//        }
//    }
//    }
//    else if(account=="controller"&&password=="0000")
//    {
//        flag=2;
// //    for (j=0;j<controller_line.length();j++) {
// //        QString line=controller_line.at(j);
// //        line=line.trimmed();
// //        QStringList linesplit=line.split(" ");
// //        if(account==linesplit.at(0)&&password==linesplit.at(1))
// //        {
// //           flag=2;
// //        }
// //    }
//    }
//    else if (account.length()<1||password.length()<1)
//    {
//        QMessageBox::critical(this,"错误","请输入账号和密码！","确认");
//        flag=3;
//    }

//    switch (flag)
//    {
//    case 0:
//    {
//        student a;
//        this->close();
//        a.exec();
//        break;
//    }
//    case 1:
//    {
//        teacher a;
//        this->close();
//        a.exec();
//        break;
//    }
//    case 2:
//    {
//        class system a;
//        this->close();
//        a.exec();
//        break;
//    }
//    case 3:
//    {
//        break;
//    }
//    default:
//    {
//        QMessageBox::critical(this,"错误","账号密码错误!\n或账号不存在!","确认");
//        break;
//    }
//    }
}



void MainWindow::on_btn_tuichu_clicked()
{
    this->close();
}

//QSqlDatabase database;
//if (QSqlDatabase::contains("qt_sql_default_connection"))
//{
//    database = QSqlDatabase::database("qt_sql_default_connection");
//}
//else
//{
//    database = QSqlDatabase::addDatabase("QSQLITE");
//    database.setDatabaseName("MyDataBase.db");
//    database.setUserName("ABC");
//    database.setPassword("123456");
//}

//if (!database.open())
//{
//    qDebug() << "Error: Failed to connect database." << database.lastError();
//}
//else
//{
//    //操作数据库
//}
//database.close();
