#pragma once
#include "singleton.h"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>

//CRTP �̳����Լ�Ϊ���͵�ģ����
class HttpMgr : public QObject, public Singleton<HttpMgr>,
    public std::enable_shared_from_this<HttpMgr> 
{
	Q_OBJECT
public:
    ~HttpMgr();
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);

public:
    friend class Singleton<HttpMgr>;
    HttpMgr();

    QNetworkAccessManager m_manager;

private slots:
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);

signals:
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);

};

// Ensure you have included the necessary Qt modules in your .pro file
// Add the following line to your .pro file to include the network module
// QT += network
