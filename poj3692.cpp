#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int maxv = 512;

int V;
vector<int> G[maxv];
int used[maxv];
int match[maxv];
int link[maxv][maxv];

void add_edge(int u, int v)
{
	G[u].push_back(v);
	G[v].push_back(u);
}

bool dfs(int v)
{
	used[v] = true;
	for(int i=0; i<(int)G[v].size(); ++i){
		int u = G[v][i], w=match[u];
		if(w==-1 || !used[w]&&dfs(w)){
			match[u] = v;
			match[v] = u;
			return true;
		}
	}
	return false;
}

int bipartite_matching()
{
	int res = 0;
	memset(match, -1, sizeof match);
	for(int i=0; i<V; ++i){
		if(match[i] < 0){
			memset(used, 0, sizeof used);
			if(dfs(i)) ++res;
		}
	}
	return res;
}

int main()
{
	int g, b, m;
	int x, y;
	int ca = 0;
	while(EOF != scanf("%d %d %d", &g, &b, &m)){
		if(g==0 && b==0 && m==0) break;
		V = g + b;
		for(int i=0; i<V; ++i)
			G[i].clear();
		memset(link, 0, sizeof(link));
		for(int i=0; i<m; ++i){
			scanf("%d %d", &x, &y);
			link[x-1][g+y-1] = 1;
		}
		for(int i=0; i<g; ++i){
			for(int j=g; j<V; ++j){
				if(link[i][j] == 0)
					add_edge(i,j);
			}
		}
		printf("Case %d: %d\n", ++ca, V-bipartite_matching());
	}
}