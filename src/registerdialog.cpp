#include "../header/registerdialog.h"
#include "../ui/ui_registerdialog.h" 
#include "../header/globle.h"
#include "../header/httpmgr.h"

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
    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish,
        this, &RegisterDialog::slot_reg_mod_finish);

    initHttpHandlers();
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
            showTip(tr("请输入正确的邮箱"),false);
        }
    }
}

void RegisterDialog::initHttpHandlers()
{
    //注册获取验证码回包的逻辑
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](const QJsonObject& json_obj){
        int error = json_obj["error"].toInt();
        if(error !=ErrorCodes::SUCCESS)
        {
            showTip(tr("参数错误"), true);
            return;
        }

        auto email = json_obj["email"].toString();
        showTip(tr("验证码已经发送到邮箱，请注意查收"), true);
        qDebug() << "email is: " << email;
    });
}

void RegisterDialog::showTip(QString tip, bool b_ok)
{
    if (b_ok)
    {
		ui->err_tip->setProperty("state", "normal");
	}
    else
    {
        ui->err_tip->setProperty("state", "err");
    }
    ui->err_tip->setText(tip);
    repolish(ui->err_tip);
    return;
}
void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if (err != ErrorCodes::SUCCESS)
    {
        showTip(tr("网络请求错误"), true);
        return;
    }

    //解析JSON 字符串 res 转化为QByteArray
    QJsonDocument json_doc = QJsonDocument::fromJson(res.toUtf8()); 
    if (json_doc.isNull())
    {
        showTip(tr("json解析失败"), true);
        return;
    }

    //json解析错误
    if (!json_doc.isObject())
    {
        showTip(tr("json解析失败"), true);
        return;
    }

    _handlers[id](json_doc.object());
    showTip(tr("注册成功"), true);
    return;
    
}
RegisterDialog::~RegisterDialog()
{
    delete ui;
}
