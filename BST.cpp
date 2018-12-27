#include<iostream>
#include<iomanip>
using namespace std;

class BinNode
{
public:
	int data;
	BinNode* left;
	BinNode* right;
	BinNode() :left(0), right(0) {}
	BinNode(int a) :data(a), left(0), right(0){}
};

class BST 
{
public:
	BST():myRoot(0){}
	~BST();//析构
	void deletehelper(BinNode* p);//析构辅助函数
	bool empty() const;//判空
	void preorder()const;//前序VLR
	void inorder()const;//中序LVR
	void postorder()const;//后序LRV
	void preorderhelper(BinNode* p)const;//前序VLR辅助函数
	void inorderhelper(BinNode* p)const;//中序LVR辅助函数
	void postorderhelper(BinNode* p)const;//后序LRV辅助函数
	void add(const int& item);//添加结点
	void remove(const int& item);//删除结点
	void graph()const;//打印树
	void graphhelper(int indent, BinNode* p)const;//打印树辅助函数
private:
	BinNode* myRoot;//根节点
};

BST::~BST()//析构
{
	deletehelper(myRoot);
}
void BST::deletehelper(BinNode* p)//析构辅助函数
{
	if (p != 0) 
	{
		deletehelper(p->left);
		deletehelper(p->right);
		delete p;
	}
}
bool BST::empty() const
{
	return myRoot == 0;
}
void BST::preorder()const//前序VLR
{
	preorderhelper(myRoot);
	cout << endl;
}
void BST::inorder()const//中序LVR
{
	inorderhelper(myRoot);
	cout << endl;
}
void BST::postorder()const//后序LRV
{
	postorderhelper(myRoot);
	cout << endl;
}

void BST::preorderhelper(BinNode* p) const//前序VLR辅助函数
{
	if (p != 0)
	{
		cout << p->data << " ";//V
		preorderhelper(p->left);//L
		preorderhelper(p->right);//R
	}
}

void BST::inorderhelper(BinNode* p) const//中序LVR辅助函数
{
	if (p != 0)
	{
		inorderhelper(p->left);//L
		cout << p->data << " ";//V
		inorderhelper(p->right);//R
	}
}
void BST::postorderhelper(BinNode* p) const//后序LRV辅助函数
{
	if (p != 0)
	{
		postorderhelper(p->left);//L
		postorderhelper(p->right);//R
		cout << p->data << " ";//V
	}
}
void BST::add(const int& item)//添加结点
{
	BinNode* locptr = myRoot;//当前指针
	BinNode* parent = 0;//当前结点的双亲
	bool found = false;//表示item已存在
	while (!found && locptr != 0)
	{
		parent = locptr;
		if (item < locptr->data)
			locptr = locptr->left;//下降到左子树
		else if (item > locptr->data)
			locptr = locptr->right;//下降到右子树
		else found == true;//数字已存在
	}
	if (!found)//当前指针为NULL
	{
		locptr = new BinNode(item);
	}
	if (parent == 0)
		myRoot = locptr;//添加结点为第一个
	else if (item < parent->data)
		parent->left = locptr;//插入左
	else
		parent->right = locptr;//插入右
}
void BST::remove(const int& item)//删除结点
{
	bool found = false;//item是否被找到
	BinNode* locptr = myRoot;//当前指针
	BinNode* parent = 0;//当前结点的双亲
	while (!found && locptr != 0)
	{
		parent = locptr;
		if (item < locptr->data)
			locptr = locptr->left;//下降到左子树
		else if (item > locptr->data)
			locptr = locptr->right;//下降到右子树
		else found == true;//找到item
	}
	if (!found) {
		cout << "结点不存在!";
		return;
	}
	if (locptr->left != 0 && locptr->right != 0)//删除结点有两个子女
	{
		BinNode* tmp = locptr->right;
		parent = locptr;
		while (tmp->left != 0)
		{
			parent = tmp;
			tmp = tmp->left;
		}
		locptr->data = tmp->data;//将删除节点最左边的结点移动到删除节点的位置上
		locptr = tmp;//待删除结点变为刚刚移动的结点的原位置
	}
	//删除结点无子女或有一个子女，同时完成双子女情况移动节点的删除
	BinNode* subtree = locptr->left;//左子树
	if (subtree == 0)
		subtree = locptr->right;//若无左子树则指向右子树
	if (parent == 0)//删除结点为根结点
		myRoot = subtree;
	else if (locptr == parent->left)//删除结点为左子女
		parent->left = subtree;
	else//删除节点为右子女
		parent->right = subtree;
	delete locptr;
}
void BST::graph()const//打印树
{
	graphhelper(0, myRoot);
}

void BST::graphhelper(int indent, BinNode* p)const//打印树辅助函数
{
	BinNode* subtree = p;
	if (p != 0)
	{
		graphhelper(indent+8,p->right);
		cout << setw(indent) << " " << p->data << endl;
		graphhelper(indent + 8, p->left);
	}
}
int main()
{
	BST test;
	int adding[] = { 23,11,56,5,20,30,89,77,45,50 };
	for (int i = 0; i < 10; i++)
	{
		test.add(adding[i]);
	}
	cout << "前序：";
	test.preorder();
	cout << "中序：";
	test.inorder();
	cout << "后序：";
	test.postorder();
	test.graph();
}