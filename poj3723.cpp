#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

const int maxn = 20010;
const int maxe = 50010;

struct edge{
	int from,to;
	int w;
	friend bool operator<(const edge &e1, const edge &e2){
		return e1.w < e2.w;
	}
}e[maxe];

bool cmp(const edge &e1, const edge &e2){
	return e1.w < e2.w;
}

struct disjoint_set{
	int rank[maxn];
	int p[maxn];
	int n;

	void init(int a){
		n = a;
		for(int i=0; i<n; ++i){
			rank[i] = 0;
			p[i] = i;
		}
	}

	int find(int x){
		if(x != p[x])
			p[x] = find(p[x]);
		return p[x];
	}

	void link(int a, int b){
		int x = find(a);
		int y = find(b);
		if(x == y) return ;
		if(rank[x] > rank[y]){
			p[y] = x;
		}else{
			p[x] = y;
			if(rank[x] == rank[y])
				++rank[y];
		}
	}
}dset;

int main()
{
	int re, n, m, r, x, y, d;
	int count, ans;
	priority_queue<edge> q;
	scanf("%d", &re);
	while(re--){
		scanf("%d %d %d", &n, &m, &r);
		dset.init(n+m);
		while(!q.empty()) q.pop();
		for(int i=0; i<r; ++i){
			scanf("%d %d %d", &x, &y, &d);
			e[i].from = x;
			e[i].to = n+y;
			e[i].w = -d;
		}
		sort(e, e+r, cmp);
		ans = 10000 * (n+m);
		for(int i=0; i<r; ++i){
			if(dset.find(e[i].from) != dset.find(e[i].to)){
				dset.link(e[i].from, e[i].to);
				ans += e[i].w;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}