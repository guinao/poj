// 当前弧优化，尝试加多路增广反而更慢T_T
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <utility>
#include <algorithm>
using namespace std;

typedef long long ll;

const int maxv = 20002;
const int inf = 999999999;

struct edge{int to, cap, rev;};
struct state{int v, cap, f; };

vector<edge> G[maxv];
int level[maxv];
int iter[maxv];
int n, m;

void add_edge(int from, int to, int cap)
{
	edge e;
	e.to = to, e.cap = cap, e.rev = (int)G[to].size();
	G[from].push_back(e);
	e.to = from, e.cap = 0, e.rev = (int)G[from].size()-1;
	G[to].push_back(e);
}

void bfs(int s)
{
	queue<int> q;
	memset(level, -1, sizeof level);
	level[s] = 0;
	q.push(s);
	while(!q.empty()){
		int v = q.front();
		q.pop();
		for(int i=0; i<(int)G[v].size(); ++i){
			edge &e = G[v][i];
			if(e.cap > 0 && level[e.to]<0){
				level[e.to] = level[v] + 1;
				q.push(e.to);
			}
		}
	}
}

int dfs(int v, int t, int f)
{
	if(v == t) return f;
	for(int& i=iter[v]; i<(int)G[v].size(); ++i){
		edge &e = G[v][i];
		if(e.cap>0 && level[v]<level[e.to]){
			int d = dfs(e.to, t, min(e.cap, f));
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
		while((f = rdfs(s, t, inf)) > 0){
			flow += f;
		}
	}
	return flow;
}

int main()
{
	int a, b, w;
	int s, t;
	while(EOF != scanf("%d %d", &n, &m)){
		s = n, t = n+1;
		for(int i=0; i<n+2; ++i)
			G[i].clear();
		for(int i=0; i<n; ++i){
			scanf("%d %d", &a, &b);
			add_edge(i, t, a);
			add_edge(s, i, b);
		}
		for(int i=0; i<m; ++i){
			scanf("%d %d %d", &a, &b, &w);
			add_edge(a-1, b-1, w);
			add_edge(b-1, a-1, w);
		}
		printf("%d\n", max_flow(s, t));
	}
	return 0;
}