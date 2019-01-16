#include <list>
#include <vector>
#include<iostream>
#include<queue>
using namespace std;
class Digraph
{
public:
	Digraph();//创建初始的图
	void display();//打印
	char getData(int k) const;//提取一个给定顶点中的数据值
	void DepthFirstSearch(int start);//从start开始进行深度优先搜索
	void DepthFirstSearch(int start,vector<bool> &unvisited);//从start开始进行深度优先搜索
	void WidthFirstSearch(int start);//从start开始进行广度优先搜索
	void WidthFirstSearch(int start, vector<bool> &unvisited);//从start开始进行广度优先搜索
private:
	class VertexInfo//头节点
	{
	public:
		char data;
		list<int> adjacencyList;
	};
	vector<VertexInfo> myAdjacencyLists;
};
Digraph::Digraph()
{
	VertexInfo sample[5];
	for (int i = 0; i < 5; i++)
	{
		sample[i].data = 'A' + i;
	}
	list<int> adjList;
	//A
	adjList.push_back(2);
	adjList.push_back(3);
	adjList.push_back(4);
	sample[0].adjacencyList = adjList;
	myAdjacencyLists.push_back(sample[0]);
	//B
	adjList.clear();
	adjList.push_back(5);
	sample[1].adjacencyList = adjList;
	myAdjacencyLists.push_back(sample[1]);
	//C
	adjList.clear();
	adjList.push_back(1);
	sample[2].adjacencyList = adjList;
	myAdjacencyLists.push_back(sample[2]);
	//D
	adjList.clear();
	adjList.push_back(5);
	sample[3].adjacencyList = adjList;
	myAdjacencyLists.push_back(sample[3]);
	//E
	adjList.clear();
	adjList.push_back(3);
	sample[4].adjacencyList = adjList;
	myAdjacencyLists.push_back(sample[4]);
}
void Digraph::display()
{
	cout << "邻接表：\n";
	for (int i = 0; i < myAdjacencyLists.size(); i++)
	{
		cout << i+1 << "：" << myAdjacencyLists[i].data << "-";
			for (list<int>::iterator it = myAdjacencyLists[i].adjacencyList.begin();
			it != myAdjacencyLists[i].adjacencyList.end(); it++)
			cout << *it << "  ";
		cout << endl;
	}
}
char Digraph::getData(int n) const
{
	return myAdjacencyLists[n].data;
}
void Digraph::DepthFirstSearch(int start)
{
	vector<bool> unvisited(myAdjacencyLists.size() , true);
	DepthFirstSearch(start, unvisited);
}
void Digraph::DepthFirstSearch(int start, vector<bool>& unvisited) 
{
	cout << myAdjacencyLists[start].data << endl;

	unvisited[start] = false;
	for (list<int>::iterator it = myAdjacencyLists[start].adjacencyList.begin();
		it != myAdjacencyLists[start].adjacencyList.end(); it++)
		if (unvisited[*it - 1])//检查当前节点是否被检查过
			DepthFirstSearch(*it-1, unvisited);//从新节点开始深度优先搜索
}
void Digraph::WidthFirstSearch(int start)
{
	vector<bool> unvisited(myAdjacencyLists.size(), true);
	WidthFirstSearch(start, unvisited);
}
void Digraph::WidthFirstSearch(int start, vector<bool>& unvisited)
{
	cout << myAdjacencyLists[start].data << endl;
	
	unvisited[start] = false;
	queue<int> wait;
	wait.push(start);	//初始化一个仅包含起始顶点的队列
	while (!wait.empty())//当队列非空时
	{
		int front = wait.front();//取队列头元素
		for (list<int>::iterator it = myAdjacencyLists[front].adjacencyList.begin();
			it != myAdjacencyLists[front].adjacencyList.end(); it++)
			if (unvisited[*it - 1])//相邻节点没访问过时
			{
				cout << myAdjacencyLists[*it-1].data << endl;//访问当前节点
				unvisited[*it - 1] = false;
				wait.push(*it - 1);//将当前节点加入队列
			}
		wait.pop();//删除队列首元素
	}
}
int main()
{
	Digraph sample;
	sample.display();
	cout << "起点为A的深度优先：\n";
	sample.DepthFirstSearch(1 - 1);
	cout << "起点为A的广度优先：\n";
	sample.WidthFirstSearch(1 - 1);
}