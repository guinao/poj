#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int maxn = 50010;

struct edge{int to, cost;};
vector<edge> es[maxn];
int dist[maxn];
bool mark[maxn];

int max(int a, int b)
{
	return a > b ? a : b;
}

int min(int a, int b)
{
	return a < b ? a : b;
}

void spfa(int n)
{
	deque<int> q;
	memset(dist, 0, sizeof dist);
	for(int i=n; i>=0; --i){
		q.push_back(i);
		mark[i] = true;
	}
	while(!q.empty()){
		int from = q.front();
		q.pop_front();
		mark[from] = false;
		for(int i=0; i<(int)es[from].size(); ++i){
			edge &e = es[from][i];
			if(dist[e.to] > dist[from] + e.cost){
				dist[e.to] = dist[from] + e.cost;
				if(!mark[e.to]){
					if(q.empty() || dist[e.to] <= dist[q.front()])
						q.push_front(e.to);
					else
						q.push_back(e.to);
					mark[e.to] = true;
				}
			}
		}
	}
}

int main()
{
	int n;
	int a, b, c;
	int s, t;
	edge e;
	while(EOF != scanf("%d", &n)){
		s = 999999999;
		t = 0;
		for(int i=0; i<n; ++i){
			scanf("%d %d %d", &a, &b, &c);
			e.cost = -c;
			e.to = a;
			es[b+1].push_back(e);
			s = min(a, s);
			t = max(t, b+1);
		}
		for(int i=0; i<t; ++i){
			e.cost = 1;
			e.to = i+1;
			es[i].push_back(e);
		}
		for(int i=1; i<=t; ++i){
			e.cost = 0;
			e.to = i-1;
			es[i].push_back(e);
		}
		spfa(t);
		printf("%d\n", dist[t]-dist[s]);
	}
	return 0;
}