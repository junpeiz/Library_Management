#include "borrow_list.h"
#include "ui_borrow_list.h"

borrow_list::borrow_list(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::borrow_list)
{
    ui->setupUi(this);
}

borrow_list::~borrow_list()
{
    delete ui;
}

void borrow_list::on_buttonBox_accepted()
{
    QString data;
    if(!ui->cno->text().isEmpty())
        data += ui->cno->text();
    emit sendData(data);
}
