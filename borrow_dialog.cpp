#include "borrow_dialog.h"
#include "ui_borrow_dialog.h"

borrow_dialog::borrow_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::borrow_dialog)
{
    ui->setupUi(this);
}

borrow_dialog::~borrow_dialog()
{
    delete ui;
}

void borrow_dialog::on_buttonBox_accepted()
{
    QString bno, cno;
    if (!ui->bno_info->text().isEmpty())
        bno += ui->bno_info->text();
    if (!ui->cno_info->text().isEmpty())
        cno += ui->cno_info->text();
    emit sendData(bno, cno);
}
