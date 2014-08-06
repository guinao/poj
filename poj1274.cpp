#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int maxv = 512;
int V;
vector<int> G[maxv];
int match[maxv];
int used[maxv];

void add_edge(int u, int v)
{
	G[u].push_back(v);
	G[v].push_back(u);
}

bool dfs(int v)
{
	used[v] = true;
	for(int i=0; i<G[v].size(); ++i){
		int u = G[v][i], w = match[u];
		if(w < 0 || !used[w]&&dfs(w)){
			match[v] = u;
			match[u] = v;
			return true;
		}
	}
	return false;
}

int bipartite_matching()
{
	int res = 0;
	memset(match, -1, sizeof match);
	for(int v=0; v<V; ++v){
		if(match[v] < 0){
			memset(used, 0, sizeof used);
			if(dfs(v))
				++res;
		}
	}
	return res;
}

int main()
{
	int n, m;
	int s, a;
	while(EOF != scanf("%d %d", &n, &m)){
		V = n+m;
		for(int i=0; i<V; ++i)
			G[i].clear();
		for(int i=0; i<n; ++i){
			scanf("%d", &s);
			for(int j=0; j<s; ++j){
				scanf("%d", &a);
				add_edge(i, n+a-1);
			}
		}
		printf("%d\n", bipartite_matching());
	}
	return 0;
}