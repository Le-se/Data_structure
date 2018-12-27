#include"User.h"
#include<iostream>
using namespace std;

void User::view()
{
	while (true)
	{
		system("cls");//����
		cout << "    -------------------------------------------\n"
			<< "     |           ��ӭʹ���˻�����ϵͳ          |\n"
			<< "     |           1.ע��                        |\n"
			<< "     |           2.��½                        |\n"
			<< "     |           3.�˳�                        |\n"
			<< "     -------------------------------------------\n"
			<< "                   ��ѡ��1/2/3!\n";
		char choice;
		cin >> choice;
		switch (choice)
		{
		case '1':signUp(); break;
		case '2':login(); break;
		case '3':return;
		default:cout << "        �������"; 
			system("pause");
		}
	}
}

void User::signUp()//ע��
{
	system("cls");//����
	string name, password;
	cout << "             ��ӭ�����˻�ע����棡\n"
		<< "               ����0����������\n\n";
	while (true)
	{
		cout << "               �������û�����";
		cin >> name;
		if (name == "0") break;
		else if (info.search(name) != NULL)
		{
			cout << "\n               ���˺��Ѵ��ڣ����������룡\n\n";
			system("pause");
		}
		else
		{
			cout << "\n               ���������룺";
			cin >> password;
			info.add(name, password);
			cout << "\n               ��ϲ��ע��ɹ���\n";
			system("pause");
			break;
		}
	}
}

void User::login()//��½
{
	while (true)
	{
		system("cls");//����
		string name, password;
		cout << "             ��ӭ�����û���¼���棡\n\n";
		cout << "               �������û�����";
		cin >> name;
		cout << "\n               ���������룺";
		cin >> password;	
		if (info.search(name) == 0)
		{
			cout << "\n               �û������ڣ�����������\n";
			system("pause");
		}
		else if (password != info.search(name)->getPass())
		{
			cout << "\n               �����������������\n";
			system("pause");
		}
		else
		{
			cout << "\n               ��½�ɹ���\n";
			system("pause");
			while (true)
			{
				system("cls");//����
				cout << "               1.�޸�����\n"
					<< "               2.ɾ���˻�\n"
					<< "               3.�˳���½\n"
					<< "               ��ѡ��1/2/3!\n";
				char choice;
				cin >> choice;
				if (choice == '3')
					return;
				else if (choice == '1')
				{
					system("cls");//����
					cout << "             ��ӭ���������޸Ľ��棡\n";
					string pass1, pass2;
					while (true)
					{
						cout << "             ������������:";
						cin >> pass1;
						cout << "\n             ���ٴ�����������:";
						cin >> pass2;
						if (pass1 != pass2)
							cout << "\n             �������벻һ�£�����������\n\n";
						else
							break;
					}
					info.search(name)->changePass(pass2);
					cout << "\n             �޸�����ɹ���\n";
					system("pause");
				}
				else if (choice == '2')
				{
					system("cls");//����
					cout << "             ɾ���ɹ���\n";
					info.remove(name);
					system("pause");
					return;
				}
				else
					cout << "             ���������룡";
			}
		}
		
	}
}