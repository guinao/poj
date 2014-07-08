#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int maxn = 50010;

struct edge{int from, to, cost;};
vector<edge> es;
int dist[maxn];

int max(int a, int b)
{
	return a > b ? a : b;
}

int min(int a, int b)
{
	return a < b ? a : b;
}

void bellman_ford(int n)
{
	for(int i=0; i<=n; ++i)
		dist[i] = 0;
	bool flag = true;
	while(flag){
		flag = false;
		for(int i=0; i<(int)es.size(); ++i){
			edge &e = es[i];
			if(dist[e.to] > dist[e.from]+e.cost){
				dist[e.to] = dist[e.from]+e.cost;
				flag = true;
			}
		}

		for(int i=0; i<n; ++i){
			if(dist[i+1] > dist[i]+1){
				dist[i+1] = dist[i]+1;
				flag = true;
			}
		}

		for(int i=n; i>0; --i){
			if(dist[i-1] > dist[i]){
				dist[i-1] = dist[i];
				flag = true;
			}
		}
	}
}

int main()
{
	int n;
	int a, b, c;
	int s, t;
	while(EOF != scanf("%d", &n)){
		es.resize(n);
		s = 999999999;
		t = 0;
		for(int i=0; i<n; ++i){
			scanf("%d %d %d", &a, &b, &c);
			es[i].from = b+1;
			es[i].to = a;
			es[i].cost = -c;
			s = min(a, s);
			t = max(t, b+1);
		}
		bellman_ford(t);
		printf("%d\n", dist[t]-dist[s]);
	}
	return 0;
}