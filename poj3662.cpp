#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

const int maxn = 1024;
const int inf = 999999999;
struct edge{ int to,cost,len; };
typedef pair<int,int> P;

vector<edge> g[maxn];
int n, p, k;
int d[maxn];

bool satisfy(int l)
{
	for(int i=0; i<n; ++i){
		for(int j=0; j<(int)g[i].size(); ++j)
			if(g[i][j].cost > l)
				g[i][j].len = 1;
			else
				g[i][j].len = 0;
	}
	priority_queue<P, vector<P>, greater<P> > pq;
	fill(d, d+n, inf);
	d[0] = 0;
	pq.push(make_pair(d[0], 0));
	while(!pq.empty()){
		P p = pq.top();
		pq.pop();
		int v = p.second;
		if(d[v] < p.first)
			continue;
		for(int i=0; i<(int)g[v].size(); ++i){
			edge e = g[v][i];
			if(d[e.to] > d[v] + e.len){
				d[e.to] = d[v] + e.len;
				pq.push(make_pair(d[e.to], e.to));
			}
		}
	}
	return d[n-1] <= k;
};

int main()
{
	int lb, ub;
	int go;
	int x, y, z;
	while(EOF != scanf("%d %d %d", &n, &p, &k)){
		for(int i=0; i<n; ++i)
			g[i].clear();
		lb = ub = -1;
		for(int i=0; i<p; ++i){
			edge e;
			scanf("%d %d %d", &x, &y, &z);
			e.to = y-1;
			e.cost = z;
			g[x-1].push_back(e);
			e.to = x-1;
			g[y-1].push_back(e);
			if(z > ub)
				ub = z+1;
		}
		go = ub;
		while(ub - lb > 1){
			int mid = (ub+lb) / 2;
			if(satisfy(mid))
				ub = mid;
			else
				lb = mid;
		}
		if(ub == go)
			puts("-1");
		else
			printf("%d\n", ub);
	}
	return 0;
}