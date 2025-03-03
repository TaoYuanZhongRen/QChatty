#include "../header/mainwindow.h"
#include "../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initMainWindow();
    loginDialog = new LoginDialog();
    setCentralWidget(loginDialog);
    loginDialog->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMainWindow()
{
    this->setWindowIcon(QIcon("./pic/QChatty.ico"));
}
