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

    // ��������ͷ���������͡����ݳ���
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));
    QNetworkReply* reply = m_manager.post(request, data);

    auto self = shared_from_this();  //��֤�ڻص������б���shared_ptr������
    QObject::connect(reply, &QNetworkReply::finished, [self, reply, req_id, mod]() {
        if (reply->error() != QNetworkReply::NoError) 
        {
            // �������
            qDebug() << "Error:" << reply->errorString();
            //�����ź�֪ͨ���
            emit self->sig_http_finish(req_id, "", ErrorCodes::ERROR_NETWORK, mod);
            reply->deleteLater();
            return;
        }
        else 
        {
            // �޴��󣬴�����Ӧ����
            QString responseData = reply->readAll();
            //�����ź�֪ͨ���
            emit self->sig_http_finish(req_id, responseData, ErrorCodes::SUCCESS, mod);
            reply->deleteLater();
            return;
        }
    });
}
void HttpMgr::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod)
{
    if (mod == Modules::REGISTERMOD) {
        //�����ź�ָ֪ͨ��ģ��http��Ӧ����
        emit sig_reg_mod_finish(id, res, err);
    }

    //if (mod == Modules::RESETMOD) {
    //    //�����ź�ָ֪ͨ��ģ��http��Ӧ����
    //    emit sig_reset_mod_finish(id, res, err);
    //}

    //if (mod == Modules::LOGINMOD) {
    //    emit sig_login_mod_finish(id, res, err);
    //}
}