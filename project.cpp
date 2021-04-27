#include <iostream>
#include <list>
#include <utility>
#include <iterator>
#define NotAVertex (-1)	
#define INF (1<<30)		//����󣬼����ɴ�
#define MAX 500

using namespace std;

static int numvertex, start;	//ȫ�־�̬����

typedef struct TableEntry
{
	list< pair<int, int> > mylist;	//����һ���б� ��һ�����ڽӵ㣬 �ڶ����Ǿ���
	bool known;		//���ڱ���Ƿ񱻷��ʹ�
	int dist;		//��ʾ����
	int path;		//��ʾ·��
}adjacency_list;

adjacency_list graph[MAX];

void graph_init()
{
	int v, w;	//v��ʾ�ڽӵ㣬w��ʾȨֵ
	int i;		
	for (i = 1; i <= numvertex; i++)
	{
		graph[i].dist = INF;	//�ȳ�ʼ������Ϊ�����
		graph[i].known = false;	
		graph[i].path = NotAVertex;
	}
	graph[start].dist = 0;
	for (i = 1; i <= numvertex; i++)	//��ʼ��ʼ���ٽ��ͱ�Ȩֵ
	{
		cout << "���붥��" << i << "���ڽӵ㼰��Ȩֵ" << endl;
		cout << "windows������س�������ctrl+z" << endl;
		while (cin >> v >> w)	
		{
			graph[i].mylist.push_back(make_pair(v, w));//fisrt��ʾ���㣬second��ʾȨ��
		}
		cin.clear();
	}
}

void dijkstra()			//dijkstra�㷨�����·����
{
	int i, j, mindist, key;
	list< pair<int, int> >::iterator it;	//һ�����ϣ���ʾһ���������ڽӵ��Ȩֵ
	for (i = 1; i <= numvertex; i++)
	{
		mindist = INF;	//�����õ�ǰѭ������С���룬�ʼĬ��Ϊ�����
		for (j = 1; j <= numvertex; j++)
		{
			//�����j����û�����ʹ������������С�ڵ�ǰ����С����
			if (!graph[j].known && graph[j].dist < mindist)	
			{
				mindist = graph[j].dist;
				key = j;	//��¼��С���������±�
			}
		}
		graph[key].known = true;	//key����㱻���ʹ�
		for (it = graph[key].mylist.begin(); it != graph[key].mylist.end(); it++)
		{
			if (!graph[it->first].known)	//��������û�����ʹ�
			{
				//���it�ľ���+mindist�ȵ�ǰ��¼�ľ���С
				if (it->second + mindist < graph[it->first].dist)
				{	
					graph[it->first].dist = it->second + mindist;
					graph[it->first].path = key;	//�ɵ�ǰλ�÷���·��
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
		cout << "��";
	}
	cout << end_vertex;
}

int main()
{
	cout << "���붥����������������·������㣺" << endl;
	cin >> numvertex;
	cin >> start;
	//�ȳ�ʼ���õ�ͼ��
	graph_init();
	//��ʼ��dijkstra���������·����
	dijkstra();
	cout << "������·����" << endl;
	//�Ȱѵ�ÿ�����·�����������Ȼ��
	for (int i = 1; i <= numvertex; i++)
	{
		cout << "�ص�" << start << "���ص�" << i << "�����·��·��Ϊ��" << endl;
		print_path(i);
		cout << endl << "���·����Ϊ" << graph[i].dist << endl << endl;
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