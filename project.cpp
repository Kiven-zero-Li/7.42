#include <iostream>
#include <list>
#include <utility>
#include <iterator>
#define NotAVertex (-1)	
#define INF (1<<30)		//无穷大，即不可达
#define MAX 500

using namespace std;

static int numvertex, start;	//全局静态变量

typedef struct TableEntry
{
	list< pair<int, int> > mylist;	//定义一个列表 第一个是邻接点， 第二个是距离
	bool known;		//用于标记是否被访问过
	int dist;		//表示距离
	int path;		//表示路径
}adjacency_list;

adjacency_list graph[MAX];

void graph_init()
{
	int v, w;	//v表示邻接点，w表示权值
	int i;		
	for (i = 1; i <= numvertex; i++)
	{
		graph[i].dist = INF;	//先初始化距离为无穷大
		graph[i].known = false;	
		graph[i].path = NotAVertex;
	}
	graph[start].dist = 0;
	for (i = 1; i <= numvertex; i++)	//开始初始化临界点和边权值
	{
		cout << "输入顶点" << i << "的邻接点及其权值" << endl;
		cout << "windows下输入回车后输入ctrl+z" << endl;
		while (cin >> v >> w)	
		{
			graph[i].mylist.push_back(make_pair(v, w));//fisrt表示顶点，second表示权；
		}
		cin.clear();
	}
}

void dijkstra()			//dijkstra算法求最短路径：
{
	int i, j, mindist, key;
	list< pair<int, int> >::iterator it;	//一个集合，表示一对整数：邻接点和权值
	for (i = 1; i <= numvertex; i++)
	{
		mindist = INF;	//先设置当前循环的最小距离，最开始默认为无穷大
		for (j = 1; j <= numvertex; j++)
		{
			//如果第j个点没被访问过，且这个距离小于当前的最小距离
			if (!graph[j].known && graph[j].dist < mindist)	
			{
				mindist = graph[j].dist;
				key = j;	//记录最小距离的起点下标
			}
		}
		graph[key].known = true;	//key这个点被访问过
		for (it = graph[key].mylist.begin(); it != graph[key].mylist.end(); it++)
		{
			if (!graph[it->first].known)	//如果这个点没被访问过
			{
				//如果it的距离+mindist比当前记录的距离小
				if (it->second + mindist < graph[it->first].dist)
				{	
					graph[it->first].dist = it->second + mindist;
					graph[it->first].path = key;	//吧当前位置放入路径
				}
			}
		}

	}
}

void print_path(int end_vertex)
{
	if (graph[end_vertex].path != NotAVertex)
	{
		print_path(graph[end_vertex].path);
		cout << "到";
	}
	cout << end_vertex;
}

int main()
{
	cout << "输入顶点的数量和所求最短路径的起点：" << endl;
	cin >> numvertex;
	cin >> start;
	//先初始化得到图：
	graph_init();
	//开始用dijkstra方法求最短路径：
	dijkstra();
	cout << "输出最短路径：" << endl;
	//先把到每个点的路径都输出来，然后
	for (int i = 1; i <= numvertex; i++)
	{
		cout << "地点" << start << "到地点" << i << "的最短路径路线为：" << endl;
		print_path(i);
		cout << endl << "最短路径长为" << graph[i].dist << endl << endl;
	}
	return 0;
}
/*
2 1
3 12

3 9
4 3

5 5

3 4
5 13
6 15

6 4



*/