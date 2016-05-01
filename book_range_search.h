#ifndef BOOK_RANGE_SEARCH_H
#define BOOK_RANGE_SEARCH_H

#include <QDialog>

namespace Ui {
class book_range_search;
}

class book_range_search : public QDialog
{
    Q_OBJECT

public:
    explicit book_range_search(QWidget *parent = 0);
    ~book_range_search();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::book_range_search *ui;

signals:
    void sendData(QString, QString, QString);
};

#endif // BOOK_RANGE_SEARCH_H
