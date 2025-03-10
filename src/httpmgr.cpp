#include "..\header\httpmgr.h"
#include <QNetworkReply> // Add this include for QNetworkReply

HttpMgr::~HttpMgr()
{

}
HttpMgr::HttpMgr()
{
    connect(this, &HttpMgr::sig_http_finish, this, &HttpMgr::slot_http_finish);
}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)
{
    QByteArray data = QJsonDocument(json).toJson();
    QNetworkRequest request(url);

    // 设置请求头：请求类型、数据长度
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));
    QNetworkReply* reply = m_manager.post(request, data);

    auto self = shared_from_this();  //保证在回调函数中保留shared_ptr的引用
    QObject::connect(reply, &QNetworkReply::finished, [self, reply, req_id, mod]() {
        if (reply->error() != QNetworkReply::NoError) 
        {
            // 处理错误
            qDebug() << "Error:" << reply->errorString();
            //发送信号通知完成
            emit self->sig_http_finish(req_id, "", ErrorCodes::ERROR_NETWORK, mod);
            reply->deleteLater();
            return;
        }
        else 
        {
            // 无错误，处理响应数据
            QString responseData = reply->readAll();
            //发送信号通知完成
            emit self->sig_http_finish(req_id, responseData, ErrorCodes::SUCCESS, mod);
            reply->deleteLater();
            return;
        }
    });
}
void HttpMgr::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod)
{
    if (mod == Modules::REGISTERMOD) {
        //发送信号通知指定模块http响应结束
        emit sig_reg_mod_finish(id, res, err);
    }

    //if (mod == Modules::RESETMOD) {
    //    //发送信号通知指定模块http响应结束
    //    emit sig_reset_mod_finish(id, res, err);
    //}

    //if (mod == Modules::LOGINMOD) {
    //    emit sig_login_mod_finish(id, res, err);
    //}
}