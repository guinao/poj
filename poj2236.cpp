#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
using namespace std;

int link[1024][1024];

struct Disjoint_Set{
	int p[1024];
	int r[1024];
	int n;

	void makeSet(int n)
	{
		this->n = n;
		for(int i=0; i<=n; ++i){
			p[i] = i;
			r[i] = 0;
		}
	}

	int findParent(int x)
	{
		if(p[x] != x){
			p[x] = findParent(p[x]);
			r[x] = r[p[x]] + 1;
		}
		return p[x];
	}

	bool isSame(int a, int b)
	{
		return findParent(a) == findParent(b);
	}

	void joinSet(int a, int b){
		if(!isSame(a, b)){
			if(r[a] > r[b]){
				p[p[a]] = p[b];
			}
			else{
				p[p[b]] = p[a];
			}
		}
	}
}dset;

int main()
{
	int n, d;
	vector<pair<int,int> > v;
	int x, y;
	char buf[32];
	bool mark[1024];
	scanf("%d %d", &n, &d);
	v.resize(n);
	memset(mark, 0, sizeof mark);
	for(int i=0; i<n; ++i){
		scanf("%d %d\n", &x, &y);
		v[i] = make_pair(x, y);
		for(int j=0; j<=i; ++j){
			int dx = v[i].first - v[j].first;
			int dy = v[i].second - v[j].second;
			if(dx*dx+dy*dy <= d*d)
				link[i][j] = link[j][i] = 1;
			else
				link[i][j] = link[j][i] = 0;
		}
	}
	dset.makeSet(n);
	while(NULL != gets(buf)){
		if(buf[0] == 'O'){
			sscanf(buf+2, "%d\n", &x);
			x--;
			if(!mark[x]){
				mark[x] = true;
				for(int j=0; j<n; ++j){
					if(j!=x && mark[j] && link[j][x]==1){
						dset.joinSet(j, x);
					}
				}
			}
		}
		else{
			sscanf(buf+2, "%d %d\n", &x, &y);
			x--, y--;
			if(dset.isSame(x, y)){
				puts("SUCCESS");
			}
			else{
				puts("FAIL");
			}
		}
	}
	return 0;
}