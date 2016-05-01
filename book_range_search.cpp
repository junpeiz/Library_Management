#include "book_range_search.h"
#include "ui_book_range_search.h"

book_range_search::book_range_search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::book_range_search)
{
    ui->setupUi(this);
}

book_range_search::~book_range_search()
{
    delete ui;
}

void book_range_search::on_buttonBox_accepted()
{
    QString atrri, low_bound, up_bound;
    if (!ui->Attri->text().isEmpty())
        atrri += ui->Attri->text();
    if (!ui->low_bound->text().isEmpty())
        low_bound += ui->low_bound->text();
    if (!ui->up_bound->text().isEmpty())
        up_bound += ui->up_bound->text();
    emit sendData(atrri, low_bound, up_bound);
}
