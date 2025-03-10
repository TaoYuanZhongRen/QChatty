#ifndef GLOBLE_H
#define GLOBLE_H

#include <QWidget>
#include <functional>
#include <QStyle>
#include <QRegularExpression>
#include <iostream>
#include <memory>
#include <QNetworkReply>

extern std::function<void(QWidget*)> repolish;

enum ReqId
{
	ID_GET_VARIFY_CODE = 1001,  //��ȡ��֤��
	ID_GET_USER = 1002, //��ȡ�û���Ϣ
};

enum Modules
{
	REGISTERMOD = 0,
};

enum ErrorCodes
{
	SUCCESS = 0,
	ERR_JSON = -1,  //json��������
	ERROR_NETWORK = -2,  //�������
};

#endif // !GLOBLE_H
