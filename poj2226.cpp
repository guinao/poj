#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int maxv = 1024;
vector<int> G[maxv];
int match[maxv];
bool used[maxv];
int V;
char grid[maxv][maxv];
int line[maxv][maxv];

void add_edge(int u, int v)
{
	G[u].push_back(v);
	G[v].push_back(u);
}

int dfs(int v)
{
	used[v] = true;
	for(int i=0; i<(int)G[v].size(); ++i){
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
			memset(used, 0, sizeof(used));
			if(dfs(i)) ++res;
		}
	}
	return res;
}

int main()
{
	int r, c;
	char pre;
	while(EOF != scanf("%d %d", &r, &c)){
		V = -1;
		memset(line, -1, sizeof line);
		for(int i=0; i<r; ++i){
			scanf("%s", grid[i]);
			pre = '.';
			for(int j=0; j<c; ++j){
				if(grid[i][j]=='*'){
					if(pre=='.')
						line[i][j] = ++V;
					else
						line[i][j] = V;
				}
				pre = grid[i][j];
			}
		}
		for(int j=0; j<c; ++j){
			pre = '.';
			for(int i=0; i<r; ++i){
				if(grid[i][j] == '*'){
					if(pre=='.')
						add_edge(line[i][j], ++V);
					else
						add_edge(line[i][j], V);
				}
				pre = grid[i][j];
			}
		}
		++V;
		printf("%d\n", bipartite_matching());
	}
	return 0;
}