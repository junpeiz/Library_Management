#ifndef BOOK_SINGLE_SEARCH_H
#define BOOK_SINGLE_SEARCH_H

#include <QDialog>

namespace Ui {
class book_single_search;
}

class book_single_search : public QDialog
{
    Q_OBJECT

public:
    explicit book_single_search(QWidget *parent = 0);
    ~book_single_search();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::book_single_search *ui;

signals:
    void sendData(QString, QString);
};

#endif // BOOK_SINGLE_SEARCH_H
