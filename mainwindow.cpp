#include <ctime>
#include <sstream>
#include <fstream>
#include <QFileDialog>
#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QMessageBox>
#include <QHBoxLayout>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "borrow_dialog.h"
#include "return_dialog.h"
#include "book_single_search.h"
#include "book_range_search.h"
#include "single_book_in_dialog.h"
#include "card_manage.h"
#include "borrow_list.h"
#include "CDataBase.h"

string host = "127.0.0.1";
string user = "root";
string pwd = "";    //Your own password
string dbn = "";    //Your database's name
CDataBase *db = new CDataBase(host, user, pwd, dbn);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    borrow_dialog dialog;
    dialog.setWindowTitle("借书");
    connect(&dialog, SIGNAL(sendData(QString, QString)), this, SLOT(receive_borrow_book(QString, QString)));
    dialog.exec();
}

void MainWindow::receive_borrow_book(QString bno, QString cno)
{
    try
    {
        db->borrow_book(bno.toStdString(), cno.toStdString());
        ui->textEdit->setText("借书成功");
    }
    catch(std::exception &e)
    {
        ui->textEdit->setText(QString(e.what()));
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    return_dialog dialog;
    dialog.setWindowTitle("还书");
    connect(&dialog, SIGNAL(sendData(QString, QString)), this, SLOT(receive_return_book(QString, QString)));
    dialog.exec();
}

void MainWindow::receive_return_book(QString bno, QString cno)
{
    try
    {
        db->return_book(bno.toStdString(), cno.toStdString());
        ui->textEdit->setText("还书成功");
    }
    catch(std::exception &e)
    {
        ui->textEdit->setText(QString(e.what()));
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    single_book_in_dialog dialog;
    dialog.setWindowTitle("单本图书入库");
    connect(&dialog, SIGNAL(sendData(QString)), this, SLOT(receive_single_book_in(QString)));
    dialog.exec();
}

void MainWindow::receive_single_book_in(QString book_info)
{
    try
    {
        db->single_into_stock(book_info.toStdString());
        ui->textEdit->setText("图书入库成功");
    }
    catch(std::exception &e)
    {
        ui->textEdit->setText(QString(e.what()));
    }
}

void MainWindow::on_bundle_book_in_clicked()
{
    try
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/", "", 0);;
        if (!fileName.isNull())
        {
            db->bundle_into_stock(fileName.toStdString());
        }
        ui->textEdit->setText("批量图书入库成功");
    }
    catch(std::exception &e)
    {
        ui->textEdit->setText(QString(e.what()));
    }
}

void MainWindow::on_book_single_search_button_clicked()
{
    book_single_search dialog;
    dialog.setWindowTitle("单值书籍查询");
    connect(&dialog, SIGNAL(sendData(QString,QString)), this, SLOT(receive_single_search_book(QString,QString)));
    dialog.exec();
}

void MainWindow::receive_single_search_book(QString attribute, QString search_key)
{
    int result_num;
    try
    {
        stringstream bookRecord(db->book_search(result_num, attribute.toStdString(), search_key.toStdString()));
        ui->tableWidget->setColumnCount(9);
        QStringList headers;
        headers << "书号" << "类别" << "书名" << "出版社" << "年份" << "作者" << "价格" << "总藏书量" << "库存";
        ui->tableWidget->clear();
        ui->tableWidget->setHorizontalHeaderLabels(headers);
        ui->tableWidget->setRowCount(result_num);

        string str;
        int index = 0;
        while (!bookRecord.eof())
        {
            std::getline(bookRecord, str);
            vector<string> attri;
            split(attri, str, ',');
            for (unsigned int i = 0; i < attri.size(); ++i)
            {
                ui->tableWidget->setItem(index, i, new QTableWidgetItem(attri[i].c_str()));
            }
            index++;
        }
        ui->textEdit->setText("查询成功，共找到" + QString::number(result_num) + "条记录");
    }
    catch (std::exception &e)
    {
        ui->textEdit->setText(QString(e.what()));
    }
}

void MainWindow::on_book_range_search_button_clicked()
{
    book_range_search dialog;
    dialog.setWindowTitle("区间书籍查询");
    connect(&dialog, SIGNAL(sendData(QString,QString,QString)), this, SLOT(receive_range_search_book(QString,QString,QString)));
    dialog.exec();
}

void MainWindow::receive_range_search_book(QString attribute,QString low_bound,QString up_bound)
{
    int result_num;
    try
    {
        stringstream bookRecord(db->book_range_search(result_num, attribute.toStdString(), low_bound.toInt(), up_bound.toInt()));
        ui->tableWidget->setColumnCount(9);
        QStringList headers;
        headers << "书号" << "类别" << "书名" << "出版社" << "年份" << "作者" << "价格" << "总藏书量" << "库存";
        ui->tableWidget->clear();
        ui->tableWidget->setHorizontalHeaderLabels(headers);
        ui->tableWidget->setRowCount(result_num);

        string str;
        int index = 0;
        while (!bookRecord.eof())
        {
            std::getline(bookRecord, str);
            vector<string> attri;
            split(attri, str, ',');
            for (unsigned int i = 0; i < attri.size(); ++i)
            {
                ui->tableWidget->setItem(index, i, new QTableWidgetItem(attri[i].c_str()));
            }
            index++;
        }
        ui->textEdit->setText("查询成功，共找到" + QString::number(result_num) + "条记录");
    }
    catch (std::exception &e)
    {
        ui->textEdit->setText(QString(e.what()));
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    card_manage dialog;
    dialog.setWindowTitle("借书证信息管理");
    connect(&dialog, SIGNAL(sendInsertData(QString)), this, SLOT(receive_insert_data(QString)));
    connect(&dialog, SIGNAL(sendUpdateData(QString,int,QString)), this, SLOT(receive_update_data(QString,int,QString)));
    connect(&dialog, SIGNAL(sendDeleteData(QString)), this, SLOT(receive_delete_data(QString)));
    dialog.exec();
}

void MainWindow::receive_insert_data(QString card_info)
{
    try
    {
        db->manage_card_insert(card_info.toStdString());
        ui->textEdit->setText(("成功新增用户借书卡数据"));
    }
    catch(std::exception &e)
    {
        ui->textEdit->setText(QString(e.what()));
    }
}

void MainWindow::receive_update_data(QString cno,int index,QString newinfo)
{
    try
    {
        db->manage_card_update(cno.toStdString(), index, newinfo.toStdString());
        ui->textEdit->setText(("成功更新用户借书卡数据"));
    }
    catch(std::exception &e)
    {
        ui->textEdit->setText(QString(e.what()));
    }
}

void MainWindow::receive_delete_data(QString cno)
{
    try
    {
        db->manage_card_delete(cno.toStdString());
        ui->textEdit->setText(("成功删除用户借书卡数据"));
    }
    catch(exception &e)
    {
        ui->textEdit->setText(QString(e.what()));
    }
}

void MainWindow::on_borrow_list_button_clicked()
{
    borrow_list dialog;
    dialog.setWindowTitle("图书借阅列表查询");
    connect(&dialog, SIGNAL(sendData(QString)), this, SLOT(receive_borrow_list_data(QString)));
    dialog.exec();
}

void MainWindow::receive_borrow_list_data(QString cno)
{
    try
    {
        int result_num;
        stringstream borrow_record(db->borrowed_list(result_num, cno.toStdString()));
        ui->tableWidget->setColumnCount(4);
        QStringList headers;
        headers << "借书证号" << "图书号" << "借出时间" << "应还时间";
        ui->tableWidget->clear();
        ui->tableWidget->setHorizontalHeaderLabels(headers);
        ui->tableWidget->setRowCount(result_num);

        string str;
        int index = 0;
        while (!borrow_record.eof())
        {
            std::getline(borrow_record, str);
            vector<string> attri;
            split(attri, str, ',');
            for (unsigned int i = 0; i < attri.size(); ++i)
            {
                if (i == 2 || i == 3){
                    std::time_t t(std::stoi(attri[i]));
                    ui->tableWidget->setItem(index, i, new QTableWidgetItem(std::asctime(std::localtime(&t))));
                }
                else{
                    ui->tableWidget->setItem(index, i, new QTableWidgetItem(attri[i].c_str()));
                }
            }
            index++;
        }
        ui->textEdit->setText("查询成功，共找到" + QString::number(result_num) + "条记录");
    }
    catch(exception &e){
        ui->textEdit->setText(QString(e.what()));
    }
}
