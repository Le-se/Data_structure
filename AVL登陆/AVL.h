#pragma once
#include<string>
class Node 
{
public:
	Node() { height = 0; data = ""; left = right = 0; }
	Node(std::string item) { height = 0; data = item; left = right = 0; }
	Node(std::string item, std::string pass) { height = 0; data = item; password = pass; left = right = 0; }
	std::string getPass();
	void changePass(const std::string pass);
	friend class AVL;
private:
	int height;//高度
	std::string data;//账户数据
	std::string password;//密码
	Node* left;
	Node* right;
};
class AVL 
{
public:
		AVL() :myRoot(0) {}
		~AVL();//析构
		void deletehelper(Node* p);//析构辅助函数
		bool empty() const;//判空
		void preorder()const;//前序VLR
		void inorder()const;//中序LVR	
		void postorder()const;//后序LRV
		void preorderhelper(Node* p)const;//前序VLR辅助函数
		void inorderhelper(Node* p)const;//中序LVR辅助函数
		void postorderhelper(Node* p)const;//后序LRV辅助函数
		Node* search(const std::string& item)const;//查找节点
		Node* add(Node* &loc, const std::string& item,const std::string& pass);//添加节点
		void add(const std::string& item,const std::string& pass);
		void remove(const std::string& item);//删除节点
		Node* removehelper(Node* &loc, Node* &p);//删除节点辅助函数
		void graph()const;//打印树
		void graphhelper(int indent, Node* p)const;//打印树辅助函数
		Node* turnleft(Node*pa);//左旋
		Node* turnright(Node*pa);//右旋
		Node* turnleftright(Node*pa);//左-右旋
		Node* turnrightleft(Node*pa);//右-左旋
		Node* maximum(Node* loc);//查找以loc为根的子女中最大的
		Node* minimum(Node* loc);//查找以loc为根的子女中最小的
		int max(int a, int b);//返回最大值
		int height(Node* p);//返回树高
private:
	Node * myRoot;//根节点
};
