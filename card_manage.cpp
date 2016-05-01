#include "card_manage.h"
#include "ui_card_manage.h"

card_manage::card_manage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::card_manage)
{
    ui->setupUi(this);
}

card_manage::~card_manage()
{
    delete ui;
}

void card_manage::on_insert_button_clicked()
{
    QString card_info;
    if(!ui->cno->text().isEmpty())
        card_info += ui->cno->text() + QString(',');
    if(!ui->name->text().isEmpty())
        card_info += ui->name->text() + QString(',');
    if(!ui->department->text().isEmpty())
        card_info += ui->department->text() + QString(',');
    if(!ui->type->text().isEmpty())
        card_info += ui->type->text();
    emit sendInsertData(card_info);
    close();
}

void card_manage::on_update_button_clicked()
{
    QString cno, newinfo;
    int index;
    if(!ui->cno->text().isEmpty())
        cno += ui->cno->text();
    if(!ui->name->text().isEmpty()){
        index = 1;
        newinfo += ui->name->text();
        emit sendUpdateData(cno, index, newinfo);
    }
    else if(!ui->department->text().isEmpty()){
        index = 2;
        newinfo += ui->department->text();
        emit sendUpdateData(cno, index, newinfo);
    }
    else if(!ui->type->text().isEmpty()){
        index = 3;
        newinfo += ui->type->text();
        emit sendUpdateData(cno, index, newinfo);
    }
    close();
}

void card_manage::on_delete_button_clicked()
{
    QString cno;
    if(!ui->cno->text().isEmpty())
        cno += ui->cno->text();
    emit sendDeleteData(cno);
    close();
}
