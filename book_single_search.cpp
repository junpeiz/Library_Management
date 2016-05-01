#include "book_single_search.h"
#include "ui_book_single_search.h"

book_single_search::book_single_search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::book_single_search)
{
    ui->setupUi(this);
}

book_single_search::~book_single_search()
{
    delete ui;
}

void book_single_search::on_buttonBox_accepted()
{
    QString atrri, atrrivalue;
    if (!ui->attribute->text().isEmpty())
        atrri += ui->attribute->text();
    if (!ui->attri_value->text().isEmpty())
        atrrivalue += ui->attri_value->text();
    emit sendData(atrri, atrrivalue);
}
