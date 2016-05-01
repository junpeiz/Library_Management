#ifndef SINGLE_BOOK_IN_DIALOG_H
#define SINGLE_BOOK_IN_DIALOG_H

#include <QDialog>

namespace Ui {
class single_book_in_dialog;
}

class single_book_in_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit single_book_in_dialog(QWidget *parent = 0);
    ~single_book_in_dialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::single_book_in_dialog *ui;

signals:
    void sendData(QString);
};

#endif // SINGLE_BOOK_IN_DIALOG_H
