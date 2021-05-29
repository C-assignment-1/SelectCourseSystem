#ifndef TEA_ADDSCORE_H
#define TEA_ADDSCORE_H

#include <QDialog>

namespace Ui {
class tea_addscore;
}

class tea_addscore : public QDialog
{
    Q_OBJECT

public:
    explicit tea_addscore(QWidget *parent = nullptr);
    tea_addscore(QWidget *parent,QString);
    ~tea_addscore();
    void writeIn(QString information);
    void setSname(QString);
    QString getSname();

private slots:
    void on_btn_addscore_add_clicked();

    void on_btn_addscore_cancel_clicked();

private:
    Ui::tea_addscore *ui;
    QString sname;
};

#endif // TEA_ADDSCORE_H
