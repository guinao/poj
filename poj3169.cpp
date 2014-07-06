#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

typedef long long ll;

const int maxe = 30000;
const int maxv = 1024;
const ll inf = 99999999999LL;

struct edge{
	int from, to;
	int cost;
};

edge es[maxe];
ll d[maxv];
int v, e;

bool bellman_ford(int s)
{
	fill(d, d+v, inf);
	d[s] = 0;
	for(int j=0; j<v; ++j)
		for(int i=0; i<e; ++i)
			if(d[es[i].to] > d[es[i].from] + es[i].cost)
				d[es[i].to] = d[es[i].from] + es[i].cost;

	for(int i=0; i<e; ++i)
		if(d[es[i].to] > d[es[i].from] + es[i].cost)
			return false;
	return true;
}

int main()
{
	int n, ml, md;
	int x, y, z;
	scanf("%d %d %d", &n, &ml, &md);
	for(int i=0; i<ml; ++i){
		scanf("%d %d %d", &x, &y, &z);
		es[i].from = x-1;
		es[i].to = y-1;
		es[i].cost = z;
	}
	for(int i=ml; i<md+ml; ++i){
		scanf("%d %d %d", &x, &y, &z);
		es[i].from = y-1;
		es[i].to = x-1;
		es[i].cost = -z;
	}
	for(int i=0; i<n-1; ++i){
		es[i+ml+md].from = i+1;
		es[i+ml+md].to = i;
		es[i+ml+md].cost = 0;
	}
	v = n;
	e = ml + md + n-1;
	bellman_ford(0);
	if(bellman_ford(0)){
		if(d[v-1] == inf){
			puts("-2");
		}else{
			printf("%lld\n", d[v-1]);
		}
	}else{
		puts("-1");
	}
	return 0;
}