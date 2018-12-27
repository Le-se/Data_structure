#include"User.h"
#include<iostream>
using namespace std;

void User::view()
{
	while (true)
	{
		system("cls");//清屏
		cout << "    -------------------------------------------\n"
			<< "     |           欢迎使用账户管理系统          |\n"
			<< "     |           1.注册                        |\n"
			<< "     |           2.登陆                        |\n"
			<< "     |           3.退出                        |\n"
			<< "     -------------------------------------------\n"
			<< "                   请选择1/2/3!\n";
		char choice;
		cin >> choice;
		switch (choice)
		{
		case '1':signUp(); break;
		case '2':login(); break;
		case '3':return;
		default:cout << "        输入错误！"; 
			system("pause");
		}
	}
}

void User::signUp()//注册
{
	system("cls");//清屏
	string name, password;
	cout << "             欢迎进入账户注册界面！\n"
		<< "               输入0返回主界面\n\n";
	while (true)
	{
		cout << "               请输入用户名：";
		cin >> name;
		if (name == "0") break;
		else if (info.search(name) != NULL)
		{
			cout << "\n               该账号已存在，请重新输入！\n\n";
			system("pause");
		}
		else
		{
			cout << "\n               请输入密码：";
			cin >> password;
			info.add(name, password);
			cout << "\n               恭喜你注册成功！\n";
			system("pause");
			break;
		}
	}
}

void User::login()//登陆
{
	while (true)
	{
		system("cls");//清屏
		string name, password;
		cout << "             欢迎进入用户登录界面！\n\n";
		cout << "               请输入用户名：";
		cin >> name;
		cout << "\n               请输入密码：";
		cin >> password;	
		if (info.search(name) == 0)
		{
			cout << "\n               用户不存在！请重新输入\n";
			system("pause");
		}
		else if (password != info.search(name)->getPass())
		{
			cout << "\n               密码错误！请重新输入\n";
			system("pause");
		}
		else
		{
			cout << "\n               登陆成功！\n";
			system("pause");
			while (true)
			{
				system("cls");//清屏
				cout << "               1.修改密码\n"
					<< "               2.删除账户\n"
					<< "               3.退出登陆\n"
					<< "               请选择1/2/3!\n";
				char choice;
				cin >> choice;
				if (choice == '3')
					return;
				else if (choice == '1')
				{
					system("cls");//清屏
					cout << "             欢迎进入密码修改界面！\n";
					string pass1, pass2;
					while (true)
					{
						cout << "             请输入新密码:";
						cin >> pass1;
						cout << "\n             请再次输入新密码:";
						cin >> pass2;
						if (pass1 != pass2)
							cout << "\n             两次输入不一致！请重新输入\n\n";
						else
							break;
					}
					info.search(name)->changePass(pass2);
					cout << "\n             修改密码成功！\n";
					system("pause");
				}
				else if (choice == '2')
				{
					system("cls");//清屏
					cout << "             删除成功！\n";
					info.remove(name);
					system("pause");
					return;
				}
				else
					cout << "             请重新输入！";
			}
		}
		
	}
}