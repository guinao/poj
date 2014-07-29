#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1<<17;
const int inf = 999999999;

int dat[maxn<<1], n;
int dp[maxn];

void init(int n_)
{
	n = 1;
	while(n < n_) n<<=1;
	fill(dat, dat+n*2, inf);
}

void update(int k, int a)
{
	k += n-1;
	dat[k] = a;
	while(k > 0){
		k = (k-1) / 2;
		dat[k] = min(dat[k*2+1], dat[k*2+2]);
	}
}

int query(int a, int b, int k, int l, int r)
{
	if(r<=a || b<=l)
		return inf;
	if(a<=l && r<=b){
		return dat[k];
	}else{
		int vl = query(a, b, k*2+1, l, (l+r)/2);
		int vr = query(a, b, k*2+2, (l+r)/2, r);
		return min(vl, vr);
	}
}

int main()
{
	int _n, m;
	int a, b;
	while(EOF != scanf("%d %d", &_n, &m)){
		init(_n);
		update(1, 0);
		dp[1] = 0;
		fill(dp, dp+_n+1, inf);
		for(int i=0; i<m; ++i){
			scanf("%d %d", &a, &b);
			int v = min(dp[b], query(a, b+1, 0, 0, n)+1);
//			printf("%d\n", v);
			dp[b] = v;
			update(b, v);
		}
		printf("%d\n", dp[_n]);
	}
	return 0;
}