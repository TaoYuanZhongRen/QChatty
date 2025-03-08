#include "../header/registerdialog.h"
#include "../ui/ui_registerdialog.h" 
#include "../header/globle.h"

#pragma execution_character_set("utf-8")

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->pass_edit->setEchoMode(QLineEdit::Password);
    ui->confirm_edit->setEchoMode(QLineEdit::Password);

    ui->err_tip->setProperty("state", "normal");
    repolish(ui->err_tip);

    connect(ui->get_code, &QPushButton::clicked, this, &RegisterDialog::onGetcodeClicked);

}
void RegisterDialog::onGetcodeClicked()
{
    auto email = ui->email_edit->text();
    if(email.isEmpty())
    {
        // email@xx.com
        QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
        bool match = regex.match(email).hasMatch();
        if(match)
        {
            //发送http验证码
        }
        else
        {
            showTip(tr("请输入正确的邮箱"));
        }
    }
}

void RegisterDialog::showTip(QString tip)
{
    ui->err_tip->setText(tip);
    ui->err_tip->setProperty("state", "err");
    repolish(ui->err_tip);
    return;
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}
