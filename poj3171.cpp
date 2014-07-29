#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

typedef long long ll;
const int maxn = 1<<17;
const ll inf = 99999999999LL;
ll dat[maxn<<1];
ll dp[maxn];
int n;

struct _cow{
	int t1, t2, s;
	bool operator<(_cow& c) const
	{
		return this->t2 < c.t2;
	}
}cow[maxn];

void init(int k)
{
	n = 1;
	while(n < k) n<<=1;
	fill(dat, dat+n*2, inf);
}

ll query(int a, int b, int k, int l, int r)
{
	ll ret = inf;
	if(r<=a || b<=l)
		ret = inf;
	else if(a<=l && r<=b)
		ret = dat[k];
	else{
		ll vl = query(a, b, k*2+1, l, (l+r)/2);
		ll vr = query(a, b, k*2+2, (l+r)/2, r);
		ret = min(vl, vr);
	}
//	printf("%d %d %d %d %d is %lld\n",a, b, k, l, r, ret);
	return ret;
}

void update(int k, ll v)
{
	k += n-1;
	dat[k] = v;
	while(k > 0){
		k = (k-1) / 2;
		dat[k] = min(dat[2*k+1], dat[2*k+2]);
	}
}

int main()
{
	int nn, m, e;
	int t1, t2, s;
	vector<int> v;
	while(EOF != scanf("%d %d %d", &nn, &m, &e)){
		v.resize(3*nn+2);
		for(int i=0; i<nn; ++i){
			scanf("%d %d %d", &t1, &t2, &s);
			cow[i].t1 = t1;
			cow[i].t2 = t2;
			cow[i].s = s;
			v[i] = t1;
			v[i+nn] = t2;
			v[i+nn*2] = t2+1;
		}
		v[nn*3] = m;
		v[nn*3+1] = e;
		sort(v.begin(), v.end());
		v.erase(unique(v.begin(), v.end()), v.end());
		for(int i=0; i<nn; ++i){
			cow[i].t1 = lower_bound(v.begin(), v.end(), cow[i].t1) - v.begin() + 1;
			cow[i].t2 = lower_bound(v.begin(), v.end(), cow[i].t2) - v.begin() + 1;
		}
		sort(cow, cow+nn);
		e = lower_bound(v.begin(), v.end(), e) - v.begin() + 1;
		init(e);
		fill(dp, dp+maxn, inf);
		dp[0] = 0;
		update(0, 0);
		for(int i=0; i<nn; ++i){
			ll v = query(cow[i].t1-1, cow[i].t2, 0, 0, n)+cow[i].s;
			if(v < dp[cow[i].t2]){
				dp[cow[i].t2] = v;
				update(cow[i].t2, v);
			}
		}
		printf("%lld\n", dp[e]==inf? -1 : dp[e]);
	}
	return 0;
}