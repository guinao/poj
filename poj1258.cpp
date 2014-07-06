#include <cstdio>
#include <queue>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 128;

struct _edge{
	int from;
	int to;
	int cost;
	_edge(int a=0, int b=0, int c=0){
		from = a;
		to = b;
		cost = c;
	}

	bool operator > (const _edge& e) const 
	{
		return this->cost > e.cost;
	}
};

priority_queue<_edge, vector<_edge>, greater<_edge> > pq;

struct disjoint_set{
	int n;
	int p[maxn];
	int r[maxn];

	void makeSet(int n)
	{
		this->n = n;
		for(int i=0; i<n; ++i){
			p[i] = i;
			r[i] = 0;
		}
	}

	int findParent(int x)
	{
		if(x != p[x]){
			p[x] = findParent(p[x]);
		}
		return p[x];
	}

	bool isSame(int a, int b)
	{
		return findParent(a) == findParent(b);
	}

	void unite(int a, int b)
	{
		a = findParent(a);
		b = findParent(b);
		if(a != b){
			if(r[a] < r[b])
				p[b] = a;
			else{
				p[a] = b;
				if(r[a] == r[b])
					++r[a];
			}
		}
	}
}dset;

int main()
{
	int n, x;
	while(EOF != scanf("%d", &n)){
		for(int i=0; i<n; ++i){
			for(int j=0; j<n; ++j){
				scanf("%d", &x);
				if(j > i)
					pq.push(_edge(i,j,x));
			}
		}
		int ans = 0;
		dset.makeSet(n);
		while(!pq.empty()){
			_edge e = pq.top();
			pq.pop();
			if(!dset.isSame(e.from, e.to)){
				dset.unite(e.from, e.to);
				ans += e.cost;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}