#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void receive_borrow_book(QString bno, QString cno);
    void receive_return_book(QString bno, QString cno);
    void receive_single_book_in(QString book_info);
    void receive_single_search_book(QString, QString);
    void receive_range_search_book(QString,QString,QString);
    void receive_insert_data(QString);
    void receive_update_data(QString, const int, QString);
    void receive_delete_data(QString);
    void receive_borrow_list_data(QString);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_bundle_book_in_clicked();

    void on_pushButton_6_clicked();

    void on_book_single_search_button_clicked();

    void on_book_range_search_button_clicked();

    void on_pushButton_5_clicked();

    void on_borrow_list_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
