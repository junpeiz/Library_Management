#include "return_dialog.h"
#include "ui_return_dialog.h"

return_dialog::return_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::return_dialog)
{
    ui->setupUi(this);
}

return_dialog::~return_dialog()
{
    delete ui;
}

void return_dialog::on_buttonBox_accepted()
{
    QString bno, cno;
    if (!ui->bno_info->text().isEmpty())
        bno += ui->bno_info->text();
    if (!ui->cno_info->text().isEmpty())
        cno += ui->cno_info->text();
    emit sendData(bno, cno);
}
