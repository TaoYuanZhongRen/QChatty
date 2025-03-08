#include "../header/mainwindow.h"
#include "../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initMainWindow();

    loginDialog = new LoginDialog(this);
    loginDialog->show();

    //������ע������
    connect(loginDialog, &LoginDialog::switchRegister, this, &MainWindow::SlotSwitchReg);
    registerDialog = new RegisterDialog(this);


    loginDialog->setWindowFlags(Qt::WindowCloseButtonHint | Qt::FramelessWindowHint);
    registerDialog->setWindowFlags(Qt::WindowCloseButtonHint | Qt::FramelessWindowHint);

    setCentralWidget(loginDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMainWindow()
{
    this->setWindowIcon(QIcon("./pic/QChatty.ico"));
}
void MainWindow::SlotSwitchReg()
{
    setCentralWidget(registerDialog);
    loginDialog->hide();
    registerDialog->show();
}
