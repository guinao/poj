#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;

const int maxv = 256;
const int inf = 1<<20;

struct edge{int from , to, len; };
vector<edge> G;

int g[maxv][maxv];
int len[maxv][maxv];
int level[maxv];
int iter[maxv];
int n, p, t;

void bfs(int s)
{
	queue<int> que;
	memset(level, 0, sizeof level);
	level[s] = 1;
	que.push(s);
	while(!que.empty()){
		int v = que.front();
		que.pop();
		for(int i=0; i<n; ++i){
			if(g[v][i] > 0 && level[i]==0){
				level[i] = level[v]+1;
				que.push(i);
			}
		}
	}
}

int dfs(int v, int t, int f)
{
	if(v == t) return f;
	for(int &i=iter[v]; i<n ;++i){
		if(g[v][i]>0 && level[v]<level[i]){
			int d = dfs(i, t, min(f, g[v][i]));
			if(d > 0){
				g[v][i] -= d;
				g[i][v] += d;
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
		while((d=dfs(s,t,inf))>0){
			flow += d;
		}
	}
	return flow;
}

int main()
{
	int a, b, l;
	edge e;
	while(EOF != scanf("%d %d %d", &n, &p, &t)){
		for(int i=0; i<n; ++i)
			fill(len[i], len[i]+n, inf);
		G.clear();
		for(int i=0; i<p; ++i){
			scanf("%d %d %d", &a, &b, &l);
			e.from = a-1;
			e.to = b-1;
			e.len = l;
			G.push_back(e);
		}
		int ub=inf, lb=0;
		while(ub > lb+1){
//			printf("%d %d\n", lb, ub);
			int mid = (lb+ub) / 2;
			memset(g, 0, sizeof g);
			for(int i=0; i<(int)G.size(); ++i){
				edge &e = G[i];
				if(e.len <= mid){
					g[e.from][e.to]++;
					g[e.to][e.from]++;
				}
			}
			if(max_flow(0, n-1) >= t)
				ub = mid;
			else
				lb = mid; 
		}
		printf("%d\n", ub);
	}
	return 0;
}