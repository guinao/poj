#include <cstdio>
#include <cstring>
#include <vector>
#include <bitset>
#include <algorithm>
using namespace std;

const int maxv = 1024;

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
	for(int i=0; i<maxv; ++i){
		for(int j=0; j<10; ++j){
			if(i & 1<<j)
				link[i][i&~(1<<j)] = 1;
			else
				link[i][i|1<<j] = 1;
		}
	}
	int n, m;
	char buf[16];
	vector<int> v;
	while(EOF != scanf("%d %d", &n, &m)){
		if(n==0 && m==0) break;
		v.clear();
		for(int i=0; i<m; ++i){
			scanf("%s", buf);
			int a=0, b=0;
			for(int i=0; buf[i]!='\0'; ++i){
				if(buf[i]=='*'){
					a = a*2+0;
					b = b*2+1;
				}else{
					a = a*2+buf[i]-'0';
					b = b*2+buf[i]-'0';
				}
			}
			v.push_back(a);
			if(a != b) v.push_back(b);
		}
		sort(v.begin(), v.end());
		v.erase(unique(v.begin(), v.end()), v.end());
		V = v.size();
		for(int i=0; i<V; ++i) G[i].clear();
		for(int i=0; i<V; ++i){
			int u = v[i];
			for(int j=i+1; j<V; ++j){
				if(link[u][v[j]])
					add_edge(i, j);
			}
		}
		printf("%d\n", V-bipartite_matching());
	}
	return 0;
}