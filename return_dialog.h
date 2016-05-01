#ifndef RETURN_DIALOG_H
#define RETURN_DIALOG_H

#include <QDialog>

namespace Ui {
class return_dialog;
}

class return_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit return_dialog(QWidget *parent = 0);
    ~return_dialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::return_dialog *ui;

signals:
    void sendData(QString, QString);
};

#endif // RETURN_DIALOG_H
