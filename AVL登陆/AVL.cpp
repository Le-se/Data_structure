#include"AVL.h"
#include<iostream>
#include<iomanip>
using namespace std;
string Node::getPass()
{
	return password;
}
void Node::changePass(const string pass)
{
	password = pass;
}
int AVL::max(int a, int b)
{
	return (a > b ? a : b);
}
AVL::~AVL()//����
{
	deletehelper(myRoot);
}
void AVL::deletehelper(Node* p)//������������
{
	if (p != 0)
	{
		deletehelper(p->left);
		deletehelper(p->right);
		delete p;
	}
}
bool AVL::empty() const
{
	return myRoot == 0;
}
void AVL::preorder()const//ǰ��VLR
{
	preorderhelper(myRoot);
	cout << endl;
}
void AVL::inorder()const//����LVR
{
	inorderhelper(myRoot);
	cout << endl;
}
void AVL::postorder()const//����LRV
{
	postorderhelper(myRoot);
	cout << endl;
}

void AVL::preorderhelper(Node* p) const//ǰ��VLR��������
{
	if (p != 0)
	{
		cout << p->data << " ";//V
		preorderhelper(p->left);//L
		preorderhelper(p->right);//R
	}
}

void AVL::inorderhelper(Node* p) const//����LVR��������
{
	if (p != 0)
	{
		inorderhelper(p->left);//L
		cout << p->data << " ";//V
		inorderhelper(p->right);//R
	}
}
void AVL::postorderhelper(Node* p) const//����LRV��������
{
	if (p != 0)
	{
		postorderhelper(p->left);//L
		postorderhelper(p->right);//R
		cout << p->data << " ";//V
	}
}
Node* AVL::add(Node* &loc,const string& item,const string& pass)//��ӽ��
{
	if (loc == 0)//�������
	{
		loc = new Node(item, pass);
	}
	else if (item < loc->data)//�½���������
	{
		loc->left = add(loc->left, item, pass);
		if (height(loc->left) - height(loc->right) == 2)
		{
			if (item < loc->left->data)
				loc = turnright(loc);//�ⲿ������
			else
				loc = turnleftright(loc);//�ڲ�����-����
		}
	}
	else if (item > loc->data)//�½���������
	{
		loc->right = add(loc->right, item, pass);
		if (height(loc->right) - height(loc->left) == 2)
		{
			if (item > loc->right->data)
				loc = turnleft(loc);//�ⲿ������
			else
				loc = turnrightleft(loc);//�ڲ�����-����
		}
	}
	else
	{
		cout << "Error add same item!";
	}
	loc->height = 1 + max(height(loc->left), height(loc->right));
	return loc;
}
void AVL::add(const string& item, const string& pass)
{
	if (myRoot == 0) 
		myRoot = new Node(item, pass);
	else
		add(myRoot, item, pass);
}
Node* AVL::removehelper(Node* &loc, Node* &p)//ɾ���ڵ㸨������
{
	if (loc == 0 || p == 0)//������ɾ���ڵ㲻����
	{
		return 0;
	}

	if (p->data < loc->data)//�½���������
	{
		loc->left = removehelper(loc->left, p);
		if (height(loc->left) - height(loc->right) == -2)
		{
			Node* tmp = loc->right;//��ƽ������һ�ڵ�
			if (height(tmp->left) > height(tmp->right))
				loc = turnrightleft(loc);//�ڲ�����-����
			else
				loc = turnleft(loc);//�ⲿ������
		}
	}
	else if (p->data > loc->data)//�½���������
	{
		loc->right = removehelper(loc->right, p);
		if (height(loc->right) - height(loc->left) == -2)
		{
			Node* tmp = loc->left;//��ƽ������һ�ڵ�
			if (height(tmp->right) > height(tmp->left))
				loc = turnleftright(loc);//�ڲ�����-����
			else
				loc = turnright(loc);//�ⲿ������
		}
	}
	else//locΪ��ɾ�����
	{
		if (loc->left != 0 && loc->right != 0)//ɾ���ڵ���������Ů
		{
			if (height(loc->left) > height(loc->right))//����������������
			{
				Node* max = maximum(loc->left);//�ҳ�ɾ���ڵ������������ڵ�
				loc->data = max->data;//�����ڵ��ƶ���ɾ���ڵ��λ��
				loc->password = max->password;
				removehelper(loc->left, max);//ɾ��ԭλ�õ����ڵ�
			}
			else//���������������߻�һ����
			{
				Node* min = minimum(loc->right);//�ҳ�ɾ���ڵ�����������С�ڵ�
				loc->data = min->data;//����С�ڵ��ƶ���ɾ���ڵ��λ��
				loc->password = min->password;
				removehelper(loc->right, min);//ɾ��ԭλ�õ���С�ڵ�
			}
		}
		else//ɾ���ڵ���һ����Ů��û����Ů
		{
			Node* tmp = loc;
			loc = (loc->left != 0) ? loc->left : loc->right;
			delete tmp;
		}
	}
	return loc;
}
void AVL::remove(const string& item)//ɾ�����
{
	Node* loc=search(item);
	removehelper(myRoot, loc);

}
void AVL::graph()const//��ӡ��
{
	graphhelper(0, myRoot);
}

void AVL::graphhelper(int indent, Node* p)const//��ӡ����������
{
	Node* subtree = p;
	if (p != 0)
	{
		graphhelper(indent + 8, p->right);
		cout << setw(indent) << " " << p->data << endl;
		graphhelper(indent + 8, p->left);
	}
}

Node* AVL::turnleft(Node* pa)//����
{
	Node* tmp = pa->right;//�¸�Ϊ��ƽ��������Ů
	pa->right = tmp->left;//�¸���ԭ���������ڲ�ƽ�����ұ�
	tmp->left = pa;//ԭ���ĸ���Ϊ�¸���������

	pa->height = 1 + max(height(pa->left), height(pa->right));
	tmp->height = 1 + max(height(tmp->left), height(tmp->right));

	return tmp;
}

Node* AVL::turnright(Node* pa)//����
{
	Node* tmp = pa->left;//�¸�Ϊ��ƽ��������Ů
	pa->left = tmp->right;//�¸���ԭ���������ڲ�ƽ�������
	tmp->right = pa;//ԭ���ĸ���Ϊ�¸���������

	pa->height = 1 + max(height(pa->left), height(pa->right));
	tmp->height = 1 + max(height(tmp->left), height(tmp->right));

	return tmp;
}

Node* AVL::turnleftright(Node* pa)//��-����ת
{
	pa->left = turnleft(pa->left);
	return turnright(pa);
}

Node* AVL::turnrightleft(Node* pa)//��-����ת
{
	pa->right = turnright(pa->right);
	return turnleft(pa);
}
Node* AVL::maximum(Node* loc)//������locΪ������Ů������
{
	if (loc == 0)
		return 0;
	while (loc->right != 0)
		loc = loc->right;
	return loc;
}Node* AVL::minimum(Node* loc)//������locΪ������Ů����С��
{
	if (loc == 0)
		return 0;
	while (loc->left != 0)
		loc = loc->left;
	return loc;
}
Node* AVL::search(const string& item)const//Ѱ�ҽڵ�
{
	Node* loc = myRoot;
	while (loc != 0 && loc->data != item)
	{
		if (item < loc->data)
			loc = loc->left;
		else
			loc = loc->right;
	}
	return loc;
}
int AVL::height(Node* p)
{
	if (p != 0)
		return p->height;
	return 0;
}
