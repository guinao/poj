//1-n 同类集，n+1-2n天敌集，2n+1-3n食物集
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 50010*3;

struct Disjoint_Set{
	int n;
	int p[maxn];
	int rank[maxn];
	void init(int a){
		n = 3*a+1;
		for(int i=0; i<=n; ++i){
			p[i] = i;
			rank[i] = 0;
		}
	}
	
	int find(int x){
		if(p[x] != x)
			p[x] = find(p[x]);
		return p[x];
	}

	void link(int a, int b){
		int x = find(a);
		int y = find(b);
		if(x == y)
			return ;
		if(rank[x] < rank[y]){
			p[x] = y;
		}else{
			p[y] = x;
			if(rank[x] == rank[y])
				rank[x] ++;
		}
	}
}dset, enemy, food;

int main()
{
	int n, k;
	int d, x, y;
	int ans = 0;
	scanf("%d %d", &n, &k);
	dset.init(n);
	for(int i=0; i<k; ++i){
		scanf("%d %d %d", &d, &x, &y);
		if(x<1 || x>n || y<1 || y>n){
			++ans;
		}else if(d == 1){
			if(dset.find(x)==dset.find(y+n) || 
				dset.find(x)==dset.find(y+2*n)){
				++ans;
			}else{
				dset.link(x, y);
				dset.link(x+n, y+n);
				dset.link(x+n*2, y+n*2);
			}
		}else{
			if(dset.find(x) == dset.find(y) ||
				dset.find(x) == dset.find(y+2*n)){
				++ans;
			}else{
				dset.link(x, y+n);
				dset.link(y, x+2*n);
				dset.link(x+n, y+2*n);
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}