#include"AVL.h"
#include<iostream>
#include<iomanip>
using namespace std;
string Node::getPass()
{
	return password;
}
string Node::getName()
{
	return data;
}
void Node::changePass(const string pass)
{
	password = pass;
}
int AVL::max(int a, int b)
{
	return (a > b ? a : b);
}
AVL::~AVL()//析构
{
	deletehelper(myRoot);
}
void AVL::deletehelper(Node* p)//析构辅助函数
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
void AVL::preorder()const//前序VLR
{
	preorderhelper(myRoot);
	cout << endl;
}
void AVL::inorder()const//中序LVR
{
	inorderhelper(myRoot);
	cout << endl;
}
void AVL::postorder()const//后序LRV
{
	postorderhelper(myRoot);
	cout << endl;
}

void AVL::preorderhelper(Node* p) const//前序VLR辅助函数
{
	if (p != 0)
	{
		cout << p->data << " ";//V
		preorderhelper(p->left);//L
		preorderhelper(p->right);//R
	}
}

void AVL::inorderhelper(Node* p) const//中序LVR辅助函数
{
	if (p != 0)
	{
		inorderhelper(p->left);//L
		cout << p->data << " ";//V
		inorderhelper(p->right);//R
	}
}
void AVL::postorderhelper(Node* p) const//后序LRV辅助函数
{
	if (p != 0)
	{
		postorderhelper(p->left);//L
		postorderhelper(p->right);//R
		cout << p->data << " ";//V
	}
}
void AVL::showinfo(std::ostream& out) const//打印数据信息
{
	showinfo(myRoot, out);
}
void AVL::showinfo(Node* p, std::ostream& out) const
{
	if (p != 0)
	{
		out << p->data << "|"<< p->password<<std::endl;//V
		showinfo(p->left,out);//L
		showinfo(p->right,out);//R
	}
}
Node* AVL::add(Node* &loc,const string& item,const string& pass)//添加结点
{
	if (loc == 0)//创建结点
	{
		loc = new Node(item, pass);
	}
	else if (item < loc->data)//下降到左子树
	{
		loc->left = add(loc->left, item, pass);
		if (height(loc->left) - height(loc->right) == 2)
		{
			if (item < loc->left->data)
				loc = turnright(loc);//外部，右旋
			else
				loc = turnleftright(loc);//内部，左-右旋
		}
	}
	else if (item > loc->data)//下降到右子树
	{
		loc->right = add(loc->right, item, pass);
		if (height(loc->right) - height(loc->left) == 2)
		{
			if (item > loc->right->data)
				loc = turnleft(loc);//外部，左旋
			else
				loc = turnrightleft(loc);//内部，右-左旋
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
Node* AVL::removehelper(Node* &loc, Node* &p)//删除节点辅助函数
{
	if (loc == 0 || p == 0)//空树或删除节点不存在
	{
		return 0;
	}

	if (p->data < loc->data)//下降到左子树
	{
		loc->left = removehelper(loc->left, p);
		if (height(loc->left) - height(loc->right) == -2)
		{
			Node* tmp = loc->right;//不平衡点的下一节点
			if (height(tmp->left) > height(tmp->right))
				loc = turnrightleft(loc);//内部，右-左旋
			else
				loc = turnleft(loc);//外部，左旋
		}
	}
	else if (p->data > loc->data)//下降到右子树
	{
		loc->right = removehelper(loc->right, p);
		if (height(loc->right) - height(loc->left) == -2)
		{
			Node* tmp = loc->left;//不平衡点的下一节点
			if (height(tmp->right) > height(tmp->left))
				loc = turnleftright(loc);//内部，左-右旋
			else
				loc = turnright(loc);//外部，右旋
		}
	}
	else//loc为待删除结点
	{
		if (loc->left != 0 && loc->right != 0)//删除节点有两个子女
		{
			if (height(loc->left) > height(loc->right))//左子树比右子树高
			{
				Node* max = maximum(loc->left);//找出删除节点左子树的最大节点
				loc->data = max->data;//将最大节点移动到删除节点的位置
				loc->password = max->password;
				removehelper(loc->left, max);//删除原位置的最大节点
			}
			else//右子树比左子树高或一样高
			{
				Node* min = minimum(loc->right);//找出删除节点右子树的最小节点
				loc->data = min->data;//将最小节点移动到删除节点的位置
				loc->password = min->password;
				removehelper(loc->right, min);//删除原位置的最小节点
			}
		}
		else//删除节点有一个子女或没有子女
		{
			Node* tmp = loc;
			loc = (loc->left != 0) ? loc->left : loc->right;
			delete tmp;
		}
	}
	return loc;
}
void AVL::remove(const string& item)//删除结点
{
	Node* loc=search(item);
	removehelper(myRoot, loc);

}
void AVL::graph()const//打印树
{
	graphhelper(0, myRoot);
}

void AVL::graphhelper(int indent, Node* p)const//打印树辅助函数
{
	Node* subtree = p;
	if (p != 0)
	{
		graphhelper(indent + 8, p->right);
		cout << setw(indent) << " " << p->data << endl;
		graphhelper(indent + 8, p->left);
	}
}

Node* AVL::turnleft(Node* pa)//左旋
{
	Node* tmp = pa->right;//新根为不平衡点的右子女
	pa->right = tmp->left;//新根的原左子树挂在不平衡点的右边
	tmp->left = pa;//原来的根变为新根的左子树

	pa->height = 1 + max(height(pa->left), height(pa->right));
	tmp->height = 1 + max(height(tmp->left), height(tmp->right));

	return tmp;
}

Node* AVL::turnright(Node* pa)//右旋
{
	Node* tmp = pa->left;//新根为不平衡点的左子女
	pa->left = tmp->right;//新根的原右子树挂在不平衡点的左边
	tmp->right = pa;//原来的根变为新根的右子树

	pa->height = 1 + max(height(pa->left), height(pa->right));
	tmp->height = 1 + max(height(tmp->left), height(tmp->right));

	return tmp;
}

Node* AVL::turnleftright(Node* pa)//左-右旋转
{
	pa->left = turnleft(pa->left);
	return turnright(pa);
}

Node* AVL::turnrightleft(Node* pa)//右-左旋转
{
	pa->right = turnright(pa->right);
	return turnleft(pa);
}
Node* AVL::maximum(Node* loc)//查找以loc为根的子女中最大的
{
	if (loc == 0)
		return 0;
	while (loc->right != 0)
		loc = loc->right;
	return loc;
}Node* AVL::minimum(Node* loc)//查找以loc为根的子女中最小的
{
	if (loc == 0)
		return 0;
	while (loc->left != 0)
		loc = loc->left;
	return loc;
}
Node* AVL::search(const string& item)const//寻找节点
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
