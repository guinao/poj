#include <cstdio>
#include <vector>
#include <queue>
#include <queue>
using namespace std;

int const maxn = 2048;

struct edge{
	int from;
	int to;
	int cost;

	edge(int a, int b, int c)
	{
		from = a;
		to = b;
		cost = c;
	}

	bool operator>(const edge &e) const
	{
		return this->cost > e.cost;
	}
};

struct disjoint_set{
	int p[maxn];
	int r[maxn];

	void maekSet(int n){
		for(int i=1; i<=n; ++i){
			p[i] = i;
			r[i] = 0;
		}
	}

	int findParent(int x){
		if(x != p[x]){
			p[x] = findParent(p[x]);
		}
		return p[x];
	}

	bool isSame(int a, int b)
	{
		return findParent(a) == findParent(b);
	}

	void link(int a, int b){
		a = findParent(a);
		b = findParent(b);
		if(a != b){
			if(r[a] < r[b]){
				p[b] = a;
			}
			else{
				if(r[a] == r[b])
					r[a]++;
				p[a] = b;
			}
		}
	}
}dset;

int main()
{
	int n, m;
	int a, b, l;
	priority_queue<edge, vector<edge>, greater<edge> > q;
	while(EOF !=scanf("%d %d", &n, &m)){
		for(int i=0; i<m; ++i){
			scanf("%d %d %d", &a, &b, &l);
			q.push(edge(a, b, l));
		}
		int cnt = 0;
		int ans = 0;
		dset.maekSet(n);
		while(cnt < n-1){
			edge e = q.top();
			q.pop();
			if(!dset.isSame(e.from, e.to)){
				ans = e.cost;
				dset.link(e.from, e.to);
				++cnt;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}