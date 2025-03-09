#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

public slots:
        void onGetcodeClicked();


private:
    void showTip(QString tip, bool b_ok);

private:
    Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
