#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>

using namespace std;
#define num 100

template<class T>
void QuickSort(vector<T> &x);//快速排序
template<class T>
void QuickSort(vector<T> &x, int left, int right);//快排辅助
template<class T>
int Split(vector<T> &x, int left, int right);//拆分列表

template<class T>
int Split(vector<T> &x, int first, int last)
{
	int left = first, right = last;
	T pivot = x[first];//基准
	while (left < right)
	{
		while (pivot < x[right])
			right--;//从右开始寻找比基准小的数，右靠左
		while (left < right && pivot >= x[left])
			left++;//从左开始寻找比基准大的数，且左右没碰头
		if (left < right)//没碰头就左右互换
		{
			T tem = x[right];
			x[right] = x[left];
			x[left] = tem;
		}
	}
	int pos = right;//碰头位置
	x[first] = x[pos];
	x[pos] = pivot;
	return pos;
}
template<class T>
void QuickSort(vector<T> &x)
{
	QuickSort(x, 0, x.size()-1);
}

template<class T>
void QuickSort(vector<T> &x,int left, int right)
{
	int pos;//基准的最终位置
	if (left < right)
	{
		pos = Split(x, left, right);
		QuickSort(x, left, pos - 1);
		QuickSort(x, pos + 1, right);
	}
}


template<class T>
void HeapSort(vector<T> &x)
{
	int size = x.size();
	for (int i = size / 2 - 1; i >= 0; i--)//从最后一个非叶子节点开始向上整理堆
	{
		adjust(x, size, i);
	}
	for (int i = size - 1; i > 0; i--)
	{
		T tem = x[0];
		x[0] = x[i];
		x[i] = tem;//将最大的数放在堆尾
		adjust(x, i, 0);
	}
}
template<class T>
void adjust(vector<T> &x, int len,int index)//调整堆
{
	int left = 2 * index + 1;//index左节点
	int right = 2 * index + 2;//index右节点
	
	int max = index;//最大节点
	if (left < len && x[left] > x[max])
		max = left;
	if (right < len && x[right] > x[max])
		max = right;

	if (max != index)//不满足堆次序
	{
		T tem = x[index];
		x[index] = x[max];
		x[max] = tem;
		adjust(x, len, max);
	}
}

template<class T>
void Display(vector<T> &x);
template<class T>
void ResetData(vector<T> &x,vector<T> &y);//使用y重置x
//......自行添加其他必要的函数声明
int main()
{
	clock_t start, finish;
	vector<int> a(num),b(num);
    int i;
    srand(time(0));//随机数种子初始化
	for(i=0;i<num;i++)
	{	a[i]=rand()%10000+1; //随机生成1-10000内的数值作为排序对象
	    b[i]=a[i];
	}
	//排序前显示数据
	cout<<"排序前"<<endl;
    Display(a);
	cout << endl;

	//快速排序
    ResetData(a,b);
	start = clock();
	QuickSort(a);
	finish = clock();
	cout << "快速排序后" << endl
		<< "用时：" << (double)(finish - start)<<"ms\n";
	Display(a);
	cout << endl;

	//堆排序
	ResetData(a,b);
	start = clock();
	HeapSort(a);
	finish = clock();
	cout<<"堆排序后"<<endl
		<< "用时：" << (double)(finish - start)<< "ms\n";
	Display(a);
	return 0;
}

template<class T>
void Display(vector<T> &x)
{    
	for(int i=0;i<num;i++)
	{	cout<<x[i]<<" ";
	    if(i%15==0 && i!=0) cout<<endl;
	}
}

template<class T>
void ResetData(vector<T> &x,vector<T> &y)//使用y重置x
{
	for(int i=0;i<num;i++)
	{
		x[i]=y[i];
	}
}
