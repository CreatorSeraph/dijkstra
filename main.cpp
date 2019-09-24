#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

constexpr int MAPSIZE = 10;
constexpr int X = -1;
constexpr int INF = -2;

struct cNode
{
	int cost[MAPSIZE];

	bool isVisited;//이미 탐색이 끝난 노드

	cNode(std::initializer_list<int> costList)
		:cost(), isVisited(false)
	{
		int i = 0;
		for (auto iter : costList)
		{
			cost[i++] = iter;
		}
	}
};

int main()
{
	//초드 노기화
	cNode node[MAPSIZE] = {
	   //1  2  3  4  5  6  7  8  9  10
		{X, 7, X, 2, 1, X, X, X, X, X}, //1
		{7, X, 1, X, X, X, X, X, X, X}, //2
		{X, 1, X, X, X, 6, X, 2, X, X}, //3
		{2, X, X, X, X, X, 3, X, X, X}, //4
		{1, X, X, X, X, X, 5, X, X, X}, //5
		{X, X, 6, X, X, X, X, X, 1, X}, //6
		{X, X, X, 3, 5, X, X, 6, X, X}, //7
		{X, X, 2, X, X, X, 6, X, 4, X}, //8
		{X, X, X, X, X, 1, X, 4, X, 3}, //9
		{X, X, X, X, X, X, X, X, 3, X}, //10
	};
	int dist[MAPSIZE];
	int prevIdx[MAPSIZE];

	constexpr int startIdx = 1;
	constexpr int endIdx = 10;
	for (int i = 0; i < MAPSIZE; ++i)
	{
		dist[i] = ((i == startIdx - 1) ? 0 : INF);//시작노드의 dist를 0으로
		prevIdx[i] = -1;
	}

	auto isFindEnd = [&node]() {
		for (auto& iter : node)
		{
			if (!iter.isVisited)
				return false;
		}
		return true;
	};

	while (!isFindEnd())
	{
		int minIdx = -1;
		int minVal = 99999999;
		for (int i = 0; i < MAPSIZE; ++i)
		{
			if (node[i].isVisited) continue;//이미 탐색을 끝낸 노드
			if (dist[i] == INF) continue;//탐색하지도 않은 노드
			if (dist[i] < minVal)
			{
				minVal = dist[i];
				minIdx = i;
			}
		}
		//가장 작은 dist값을 가진 인덱스를 골라낸다

		for (int i = 0; i < MAPSIZE; ++i)
		{
			auto& iter = node[minIdx];
			auto& nowDist = dist[minIdx];
			int cost = iter.cost[i];
			if (iter.isVisited) continue;
			if (cost == X) continue;
			if (dist[i] == INF || dist[i] > nowDist + cost)
			{
				dist[i] = nowDist + cost;
				prevIdx[i] = minIdx;
			}
		}

		cout << minIdx + 1 << endl;
		for (int i = 0; i < MAPSIZE; ++i)
		{
			cout << i + 1 << "\t";
		}
		cout << endl;
		for (int i = 0; i < MAPSIZE; ++i)
		{
			cout << dist[i] << "\t";
		}
		cout << endl;
		for (int i = 0; i < MAPSIZE; ++i)
		{
			cout << prevIdx[i] + 1 << "\t";
		}
		cout << endl << endl;

		node[minIdx].isVisited = true;
	}

}


/*
1
1       2       3       4       5       6       7       8       9       10
0       7       -2      2       1       -2      -2      -2      -2      -2
0       1       0       1       1       0       0       0       0       0

5
1       2       3       4       5       6       7       8       9       10
0       7       -2      2       1       -2      6       -2      -2      -2
0       1       0       1       1       0       5       0       0       0

4
1       2       3       4       5       6       7       8       9       10
0       7       -2      2       1       -2      5       -2      -2      -2
0       1       0       1       1       0       4       0       0       0

7
1       2       3       4       5       6       7       8       9       10
0       7       -2      2       1       -2      5       11      -2      -2
0       1       0       1       1       0       4       7       0       0

2
1       2       3       4       5       6       7       8       9       10
0       7       8       2       1       -2      5       11      -2      -2
0       1       2       1       1       0       4       7       0       0

3
1       2       3       4       5       6       7       8       9       10
0       7       8       2       1       14      5       10      -2      -2
0       1       2       1       1       3       4       3       0       0

8
1       2       3       4       5       6       7       8       9       10
0       7       8       2       1       14      5       10      14      -2
0       1       2       1       1       3       4       3       8       0

6
1       2       3       4       5       6       7       8       9       10
0       7       8       2       1       14      5       10      14      -2
0       1       2       1       1       3       4       3       8       0

9
1       2       3       4       5       6       7       8       9       10
0       7       8       2       1       14      5       10      14      17
0       1       2       1       1       3       4       3       8       9

10
1       2       3       4       5       6       7       8       9       10
0       7       8       2       1       14      5       10      14      17
0       1       2       1       1       3       4       3       8       9
*/