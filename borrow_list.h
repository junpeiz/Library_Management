#ifndef BORROW_LIST_H
#define BORROW_LIST_H

#include <QDialog>

namespace Ui {
class borrow_list;
}

class borrow_list : public QDialog
{
    Q_OBJECT

public:
    explicit borrow_list(QWidget *parent = 0);
    ~borrow_list();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::borrow_list *ui;

signals:
    void sendData(QString);
};

#endif // BORROW_LIST_H
