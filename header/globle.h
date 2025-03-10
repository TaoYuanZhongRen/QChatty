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
	ID_GET_VARIFY_CODE = 1001,  //获取验证码
	ID_GET_USER = 1002, //获取用户信息
};

enum Modules
{
	REGISTERMOD = 0,
};

enum ErrorCodes
{
	SUCCESS = 0,
	ERR_JSON = -1,  //json解析错误
	ERROR_NETWORK = -2,  //网络错误
};

#endif // !GLOBLE_H
