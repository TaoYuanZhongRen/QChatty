#pragma once
#include <QMainWindow>
#include "logindialog.h"
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
private:
    Ui::MainWindow *ui;
    LoginDialog *loginDialog;
};
