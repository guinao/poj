#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int maxv = 1024;

vector<int> G[maxv];
int match[maxv];
int used[maxv];
int V;

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
			if(dfs(i))
				++res;
		}
	}
	return res;
}

int main()
{
	int n, k;
	int r, c;
	while(EOF != scanf("%d %d", &n, &k)){
		V = n * 2;
		for(int i=0; i<V; ++i)
			G[i].clear();
		for(int i=0; i<k; ++i){
			scanf("%d %d", &r, &c);
			add_edge(r-1, n+c-1);
		}
		printf("%d\n", bipartite_matching());
	}
}