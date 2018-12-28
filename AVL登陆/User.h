#pragma once
#include"AVL.h"
class User
{
public:
	User();//构造函数
	void view();//主界面
	void signUp();//注册
	void login();//登陆界面
	void infowrite();//写文件
	void inforead();//读文件
private:
	AVL info;//用户信息
};
