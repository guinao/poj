#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;

typedef pair<int,int> P;

struct edge{int to, cap, cost, rev; };
const int maxv = 1024;
const int inf = 999999999;

int V;
vector<edge> G[maxv];
int h[maxv];
int dist[maxv];
int prevv[maxv], preve[maxv];

void add_edge(int from, int to, int cap, int cost)
{
	edge e;
	e.to = to, e.cap=cap, e.cost=cost, e.rev=G[to].size();
	G[from].push_back(e);
	e.to = from, e.cap=0, e.cost=-cost, e.rev=G[from].size()-1;
	G[to].push_back(e);
}

int min_cost_flow(int s, int t, int f)
{
	int res = 0;
	fill(h, h+V, 0);
	while(f > 0){
		priority_queue<P, vector<P>, greater<P> > que;
		fill(dist, dist+V, inf);
		dist[s] = 0;
		que.push(P(0, s));
		while (!que.empty()){
			P p = que.top();
			que.pop();
			int v = p.second;
			if(dist[v] < p.first) continue;
			for(int i=0; i<G[v].size(); ++i){
				edge &e = G[v][i];
				if(e.cap > 0 && dist[e.to]>dist[v]+e.cost+h[v]-h[e.to]){
					dist[e.to] = dist[v]+e.cost+h[v]-h[e.to];
					prevv[e.to] = v;
					preve[e.to] = i;
					que.push(P(dist[e.to], e.to));
				}
			}
		}
		if(dist[t] == inf)
			return -1;

		for(int v = 0; v<V; ++v)
			h[v] += dist[v];

		int d = f;
		for(int v=t; v!=s; v=prevv[v]){
			int i = prevv[v], j = preve[v];
			d = min(d, G[i][j].cap);
		}
		f -= d;
		res += d * h[t];
		for(int v = t; v!=s; v=prevv[v]){
			edge &e = G[prevv[v]][preve[v]];
			e.cap -= d;
			G[v][e.rev].cap += d;
		}
	}
	return res;
}

int main()
{
	int n, m;
	int a, b, c;
	while(EOF != scanf("%d %d", &n, &m)){
		V = n;
		for(int i=0; i<m; ++i){
			scanf("%d %d %d", &a, &b, &c);
			add_edge(a-1, b-1, 1, c);
			add_edge(b-1, a-1, 1, c);
		}
		printf("%d\n", min_cost_flow(0, n-1, 2));
	}
	return 0;
}