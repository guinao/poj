#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int maxn = 1024;
const int inf = 999999999;
typedef pair<int, pair<int,int> > edge;

struct disjoint_set{
	int p[maxn];
	int r[maxn];
	int s[maxn];

	void makeSet(int n){
		for(int i=1; i<=n; ++i){
			p[i] = i;
			r[i] = 0;
			s[i] = 1;
		}
	}

	int findParent(int x){
		if(x != p[x]){
			p[x] = findParent(p[x]);
		}
		return p[x];
	}

	bool isSame(int a, int b){
		return findParent(a) == findParent(b);
	}

	void link(int a, int b){
		a = findParent(a);
		b = findParent(b);
		if(a != b){
			if(r[a] > r[b]){
				p[a] = b;
				s[b] += s[a];
			}
			else{
				if(r[a] == r[b])
					r[b] ++;
				p[b] = a;
				s[a] += s[b];
			}
		}
	}
}dset;

int main()
{
	int n, m;
	int a, b, c;
	priority_queue<edge> q;
	while(EOF != scanf("%d %d", &n, &m)){
		dset.makeSet(n);
		for(int i=0; i<m; ++i){
			scanf("%d %d %d", &a, &b, &c);
			pair<int,int> e = make_pair(a, b);
			q.push(make_pair(c, e));
		}
		int ans = 0;
		while(!q.empty()){
			edge e = q.top();
			q.pop();
			if(!dset.isSame(e.second.first, e.second.second)){
				ans += e.first;
				dset.link(e.second.first, e.second.second);
			}
		}
		a = dset.findParent(1);
		if(dset.s[a] == n){
			printf("%d\n", ans);
		}
		else{
			puts("-1");
		}
	}
	return 0;
}