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
int n;

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
	int flow = 0;
	for(int &i=iter[v]; i<n&&f ;++i){
		if(g[v][i]>0 && level[v]<level[i]){
			int d = dfs(i, t, min(f, g[v][i]));
			if(d > 0){
				g[v][i] -= d;
				g[i][v] += d;
				flow += d;
				f -= d;
			}
		}
	}
	return flow;
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
	int k, c, m;
	int a, b, l;
	edge e;
	vector<int> v;
	while(EOF != scanf("%d %d %d", &k, &c, &m)){
		n = k+c+2;
		for(int i=0; i<k+c; ++i){
			for(int j=0; j<k+c; ++j){
				scanf("%d", &l);
				len[i][j] = l>0 ? l : inf;
			}
		}
		for(int kk=0; kk<k+c; ++kk)
			for(int i=0; i<k+c; ++i)
				for(int j=0; j<k+c; ++j)
					if(len[i][kk]<inf && len[kk][j]<inf)
						len[i][j] = min(len[i][j], len[i][kk]+len[kk][j]);
		for(int i=0; i<k+c; ++i)
			for(int j=0; j<k+c; ++j) if(len[i][j] < inf)
				v.push_back(len[i][j]);
		sort(v.begin(), v.end());
		v.erase(unique(v.begin(), v.end()), v.end());
		int ub=v.size()-1, lb=-1;
		while(ub > lb+1){
			int mid = (lb+ub) / 2;
			int val = v[mid];
			memset(g, 0, sizeof g);
			for(int i=0; i<k; ++i){
				for(int j=k; j<k+c; ++j) if(len[i][j]<=val){
					g[i][j] = 1;
				}
				g[n-2][i] = m;
			}
			for(int j=0; j<c; ++j){
				g[j+k][n-1] = 1;
			}
			if(max_flow(n-2, n-1) >= c)
				ub = mid;
			else
				lb = mid;
		}
		printf("%d\n", v[ub]);
	}
	return 0;
}