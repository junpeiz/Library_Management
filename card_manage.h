#ifndef CARD_MANAGE_H
#define CARD_MANAGE_H

#include <QDialog>

namespace Ui {
class card_manage;
}

class card_manage : public QDialog
{
    Q_OBJECT

public:
    explicit card_manage(QWidget *parent = 0);
    ~card_manage();

private slots:

    void on_insert_button_clicked();

    void on_update_button_clicked();

    void on_delete_button_clicked();

private:
    Ui::card_manage *ui;

signals:
    void sendInsertData(QString);
    void sendUpdateData(QString, const int, QString);
    void sendDeleteData(QString);
};

#endif // CARD_MANAGE_H
