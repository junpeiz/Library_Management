#ifndef BORROW_DIALOG_H
#define BORROW_DIALOG_H

#include <QDialog>

namespace Ui {
class borrow_dialog;
}

class borrow_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit borrow_dialog(QWidget *parent = 0);
    ~borrow_dialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::borrow_dialog *ui;

signals:
    void sendData(QString, QString);
};

#endif // BORROW_DIALOG_H
