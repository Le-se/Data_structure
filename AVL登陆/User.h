#pragma once
#include"AVL.h"
class User
{
public:
	void view();//主界面
	void signUp();//注册
	void login();//登陆界面
private:
	AVL info;//用户信息
};
