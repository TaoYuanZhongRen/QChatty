#pragma once
#include <QMainWindow>
#include "logindialog.h"
#include "registerdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui 
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initMainWindow();

public slots:
	void SlotSwitchReg();


private:
    Ui::MainWindow *ui;
    LoginDialog *loginDialog;
    RegisterDialog *registerDialog;
};
