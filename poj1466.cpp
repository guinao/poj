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
	int n;
	int x;
	while(EOF != scanf("%d", &V)){
		for(int i=0; i<V; ++i)
			G[i].clear();
		for(int i=0; i<V; ++i){
			scanf("%*d: (%d)", &n);
			for(int j=0; j<n; ++j){
				scanf("%d", &x);
				if(x > i) add_edge(i, x);
			}
		}
		printf("%d\n", V-bipartite_matching());
	}
	return 0;
}