#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 32;
const int maxv = maxn * 2;

struct slide{
	int x1, x2, y1, y2;
	bool contains(int x, int y){
		return x1<=x && x<=x2 && y1<=y && y<=y2;
	}
}s[maxn];

int V;
vector<int> G[maxv];
int match[maxv];
int out[maxv];
int used[maxv];
bool need[maxv];

void add_edge(int u, int v)
{
	G[u].push_back(v);
	G[v].push_back(u);
}

void remove_edge(int u, int v)
{
	G[u].erase(find(G[u].begin(), G[u].end(), v));
	G[v].erase(find(G[v].begin(), G[v].end(), u));
}

bool dfs(int v)
{
	used[v] = true;
	for(int i=0; i<(int)G[v].size(); ++i){
		int u=G[v][i], w = match[u];
		if(w==-1 || !used[w]&&dfs(w)){
			match[u] = v;
			match[v] = u;
			return true;
		}
	}
	return false;
}

int bipartite_match(){
	int res = 0;
	memset(match, -1, sizeof match);
	for(int v=0; v<V; v++){
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
	int n;
	int x1, x2, y1, y2;
	int ca = 0;
	while(EOF != scanf("%d", &n)){
		if(n == 0) break;
		V = n * 2;
		for(int i=0; i<V; ++i)
			G[i].clear();
		for(int i=0; i<n; ++i){
			scanf("%d %d %d %d", &x1, &x2, &y1, &y2);
			s[i].x1 = x1;
			s[i].x2 = x2;
			s[i].y1 = y1;
			s[i].y2 = y2;
		}
		for(int i=0; i<n; ++i){
			scanf("%d %d", &x1, &y1);
			for(int j=0; j<n; ++j){
				if(s[j].contains(x1, y1))
					add_edge(j, i+n);
			}
		}
		printf("Heap %d\n", ++ca);
		int res = bipartite_match();
		int ans = 0;
		memcpy(out, match, sizeof out);
		memset(need, false, sizeof need);
		for(int i=0; i<n; ++i) if(out[i] != -1){
			remove_edge(i, out[i]);
			if(bipartite_match() < res){
				need[i] = true;
				++ans;
			}
			add_edge(i, out[i]);
		}
		if(ans > 0){
			int cnt = 0;
			for(int i=0; i<n; ++i){
				if(need[i]){
					printf("(%c,%d)%c", 'A'+i, out[i]-n+1, ans==++cnt?'\n':' ');
				}
			}
		}else{
			printf("none\n");
		}
		putchar('\n');
	}
	return 0;
}