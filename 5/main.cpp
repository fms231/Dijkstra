#include<iostream>
#include<set>

using namespace std;

const int MAX=1000;

struct edge
{
	int start;
	int end;
	int weight;
};

struct heap
{
	int num;
	int dis;
};

int grp_array(int* dis, int* flag, int N)
{
	int min, min_index;
	min_index = 0;
	min = 1000;
	for (int i = 0; i < N; i++)
	{
		if (min > dis[i] && !flag[i])
		{
			min = dis[i];
			min_index = i;
		}
	}
	flag[min_index] = 1;
	return min_index;
}

int MinHeap(struct heap* grp_heap, int num)
{
	if (num == 1)
	{
		return grp_heap[0].num;
	}
	else
	{
		while (num > 1)
		{
			if (grp_heap[num - 1].dis < grp_heap[(num - 1) / 2 - 1].dis)
			{
				struct heap temp = grp_heap[num - 1];
				grp_heap[num - 1] = grp_heap[(num - 1) / 2 - 1];
				grp_heap[(num - 1) / 2 - 1] = temp;
			}
			num--;
		}
		return grp_heap[0].num;
	}
}

void djstl(int* dis, struct edge* grp_edge, int edge_number, int N)
{
	dis[0] = 0;
	for (int i = 1; i < N; i++)
	{
		dis[i] = MAX;
	}
	set<int> node;
	node.insert(0);

	int* flag = new int[N];
	flag[0] = 1;
	for (int i = 1; i < N; i++)
	{
		flag[i] = 0;
	}
	//使用数组实现优先级队列
	/*
	for (int j = 1; j < N; j++)
	{
		for (set<int>::iterator it = node.begin(); it != node.end(); it++)
		{
			for (int i = 0; i < edge_number; i++)
			{
				if ((grp_edge[i].start == *it) && !flag[grp_edge[i].end])
				{
					if(dis[grp_edge[i].start] + grp_edge[i].weight < dis[grp_edge[i].end])
						dis[grp_edge[i].end] = dis[grp_edge[i].start] + grp_edge[i].weight;
				}
			}
		}
		node.insert(grp_array(dis, flag, N));
	}*/
	//最小堆实现优先级队列
	for (int j = 1; j < N; j++)
	{
		for (set<int>::iterator it = node.begin(); it != node.end(); it++)
		{
			for (int i = 0; i < edge_number; i++)
			{
				if ((grp_edge[i].start == *it) && !flag[grp_edge[i].end])
				{
					if (dis[grp_edge[i].start] + grp_edge[i].weight < dis[grp_edge[i].end])
						dis[grp_edge[i].end] = dis[grp_edge[i].start] + grp_edge[i].weight;
				}
			}
		}
		int num = N - node.size();
		heap* grp_heap = new struct heap[num];
		int k = 0;
		for (int i = 0; i < N; i++)
		{
			if (node.count(i))
				continue;
			grp_heap[k].num = i;
			grp_heap[k].dis = dis[i];
			k++;
		}
		node.insert(MinHeap(grp_heap, num));
	}
}

int main()
{
	int N;
	int edge_number;
	cout << "please input the number of nodes:" << endl;
	cin >> N;
	cout << "please input the number of edges:" << endl;
	cin >> edge_number;
	cout << "please input the data of edges:" << endl;
	
	edge* grp_edge = new struct edge[edge_number];
	int* dis = new int[N];
	for (int i = 0; i < edge_number; i++)
	{
		cin >> grp_edge[i].start >> grp_edge[i].end >> grp_edge[i].weight;
	}
	djstl(dis, grp_edge, edge_number, N);
	for (int i = 1; i < N; i++)
	{
		cout << '0' << "->" << i << ":" << dis[i] << endl;
	}
}
