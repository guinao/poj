#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int maxv = 512;
const int inf = 999999999;

struct edge{ int to, cap, rev; };
vector<edge> G[maxv];
int level[maxv];
int iter[maxv];

void add_edge(int from, int to, int cap)
{
	edge e;
	e.to = to;e.cap = cap;e.rev=G[to].size();
	G[from].push_back(e);
	e.to = from;e.cap = 0;e.rev=G[from].size()-1;
	G[to].push_back(e);
}

void bfs(int s)
{
	queue<int> que;
	memset(level, 0, sizeof level);
	level[s] = 1;
	que.push(s);
	while(!que.empty()){
		int v = que.front();
		que.pop();
		for(int i=0; i<(int)G[v].size(); ++i){
			edge &e = G[v][i];
			if(e.cap>0 && level[e.to]==0){
				level[e.to] = level[v]+1;
				que.push(e.to);
			}
		}
	}
}

int dfs(int v, int t, int f)
{
	if(v == t) return f;
	for(int &i=iter[v]; i<G[v].size(); ++i){
		edge &e = G[v][i];
		if(e.cap>0 && level[e.to]>level[v]){
			int d = dfs(e.to, t, min(f, e.cap));
			if(d > 0){
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}

int max_flow(int s, int t)
{
	int flow = 0;
	for(;;){
		bfs(s);
		if(level[t] == 0) return flow;
		memset(iter, 0, sizeof iter);
		int d;
		while((d=dfs(s, t, inf))>0){
			flow += d;
		}
	}
	return flow;
}

int main()
{
	int n, f, d;
	int a, b, c;
	while(EOF != scanf("%d %d %d", &n, &f, &d)){
		for(int i=1; i<=n; ++i){
			add_edge(f+i, f+n+i, 1);
			scanf("%d %d", &a, &b);
			for(int j=0; j<a; ++j){
				scanf("%d", &c);
				add_edge(c, f+i, 1);
			}
			for(int j=0; j<b; ++j){
				scanf("%d", &c);
				add_edge(f+n+i, f+2*n+c, 1);
			}
		}
		for(int i=1; i<=f; ++i){
			add_edge(0, i, 1);
		}
		for(int i=1; i<=d; ++i){
			add_edge(f+2*n+i, f+2*n+d+1, 1);
		}
		printf("%d\n", max_flow(0, f+2*n+d+1));
	}
	return 0;
}