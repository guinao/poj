#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int maxv = 256;
const int inf = 999999999;

struct edge{int to, cap, rev; };
vector<edge> G[maxv];
int level[maxv];
int iter[maxv];

void add_edge(int from, int to, int cap)
{
	edge e;
	e.to=to; e.cap=cap; e.rev=G[to].size();
	G[from].push_back(e);
	e.to=from; e.cap=0; e.rev=G[from].size()-1;
	G[to].push_back(e);
}

void bfs(int s)
{
	queue<int> que;
	memset(level, -1, sizeof level);
	level[s] = 0;
	que.push(s);
	while(!que.empty()){
		int v = que.front();
		que.pop();
		for(int i=0; i<(int)G[v].size(); ++i){
			edge &e = G[v][i];
			if(e.cap>0 && level[e.to]<0){
				level[e.to] = level[v]+1;
				que.push(e.to);
			}
		}
	}
}

int dfs(int v, int t, int f)
{
	if(v == t) return f;
	for(int &i=iter[v]; i<(int)G[v].size(); ++i){
		edge &e = G[v][i];
		if(e.cap>0 && level[v]<level[e.to]){
			int d = dfs(e.to, t, min(f, e.cap));
			if(d > 0){
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	level[v] = -1;
	return 0;
}

int max_flow(int s, int t)
{
	int flow = 0;
	for(;;){
		bfs(s);
		if(level[t] < 0) return flow;
		memset(iter, 0, sizeof iter);
		int f;
		while((f=dfs(s,t,inf))>0){
			flow += f;
		}
	}
	return flow;
}

int main()
{
	int n, m;
	int s, e, c;
	while(EOF != scanf("%d %d", &n, &m)){
		for(int i=0; i<m; ++i)
			G[i].clear();
		for(int i=0; i<n; ++i){
			scanf("%d %d %d", &s, &e, &c);
			add_edge(s-1, e-1, c);
		}
		printf("%d\n", max_flow(0, m-1));
	}
	return 0;
}