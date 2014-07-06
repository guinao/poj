#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

const int maxn = 1024;
const int inf = 999999999;
typedef pair<int,int> T;

struct edge{
	int to;
	int cost;
	edge(int a=0, int b=0){
		to = a;
		cost = b;
	}
};

vector<edge> ve[maxn];
vector<edge> rve[maxn];

void dijkstra(int s, int n,int d[maxn])
{
	priority_queue<T, vector<T>, greater<T> > pq;
	for(int i=1; i<=n; ++i)
		d[i] = inf;
	d[s] = 0;
	pq.push(make_pair(0, s));
	while(!pq.empty()){
		T cur = pq.top();
		pq.pop();
		int a = cur.second;
		if(d[a] < cur.first)
			continue;
		for(int i=0; i<ve[a].size(); ++i){
			edge e = ve[a][i];
			if(d[e.to] > d[a] + e.cost){
				d[e.to] = d[a] + e.cost;
				pq.push(make_pair(d[e.to], e.to));
			}
		}
	}
	int rd[maxn];
	fill(rd+1, rd+n+1, inf);
	rd[s] = 0;
	pq.push(make_pair(0, s));
	while(!pq.empty()){
		T cur = pq.top();
		pq.pop();
		int a = cur.second;
		if(rd[a] < cur.first)
			continue;
		for(int i=0; i<rve[a].size(); ++i){
			edge e = rve[a][i];
			if(rd[e.to] > rd[a] + e.cost){
				rd[e.to] = rd[a] + e.cost;
				pq.push(make_pair(rd[e.to], e.to));
			}
		}
	}
	for(int i=1; i<=n; ++i){
		d[i] += rd[i];
	}
}

int main()
{
	int n, m, x;
	int a, b, c;
	int d[maxn];
	while(EOF != scanf("%d %d %d", &n, &m, &x)){
		for(int i=1; i<=n; ++i){
			ve[i].clear();
			rve[i].clear();
		}
		for(int i=0; i<m; ++i){
			scanf("%d %d %d", &a, &b, &c);
			ve[a].push_back(edge(b,c));
			rve[b].push_back(edge(a,c));
		}
		dijkstra(x, n, d);
		int ans = 00;
		for(int i=1; i<=n; ++i){
			ans = max(ans, d[i]);
		}
		printf("%d\n", ans);
	}
	return 0;
}