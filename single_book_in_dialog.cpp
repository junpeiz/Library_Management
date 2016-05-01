#include "single_book_in_dialog.h"
#include "ui_single_book_in_dialog.h"

single_book_in_dialog::single_book_in_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::single_book_in_dialog)
{
    ui->setupUi(this);
}

single_book_in_dialog::~single_book_in_dialog()
{
    delete ui;
}

void single_book_in_dialog::on_buttonBox_accepted()
{
    QString str;
    if (!ui->lineEdit->text().isEmpty())
        str += ui->lineEdit->text() + ",";
    if (!ui->lineEdit_2->text().isEmpty())
        str += ui->lineEdit_2->text() + ",";
    if (!ui->lineEdit_3->text().isEmpty())
        str += ui->lineEdit_3->text() + ",";
    if (!ui->lineEdit_4->text().isEmpty())
        str += ui->lineEdit_4->text() + ",";
    if (!ui->lineEdit_5->text().isEmpty())
        str += ui->lineEdit_5->text() + ",";
    if (!ui->lineEdit_6->text().isEmpty())
        str += ui->lineEdit_6->text() + ",";
    if (!ui->lineEdit_7->text().isEmpty())
        str += ui->lineEdit_7->text() + ",";
    if (!ui->lineEdit_8->text().isEmpty())
        str += ui->lineEdit_8->text() + ",";
    if (!ui->lineEdit_9->text().isEmpty())
        str += ui->lineEdit_9->text();
    emit sendData(str);
}
