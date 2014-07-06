#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>
using namespace std;

const int maxn = 20000;
typedef long long ll;
pair<int,int> v[maxn];
ll bit0[maxn+1], bit1[maxn+1];
int len;

void add(ll *bit, int i, int x)
{
	while(i <= len){
		bit[i] += x;
		i += i & -i;
	}
}

ll sum(ll *bit, int i)
{
	ll s = 0;
	while(i > 0){
		s += bit[i];
		i -= i & -i;
	}
	return s;
}

int main()
{
	int n;
	int a, b;
	ll ans;
	ll tot0, tot1;
	while(EOF != scanf("%d", &n)){
		len = 0;
		for(int i=0; i<n; ++i){
			scanf("%d %d", &a, &b);
			v[i].first = a;
			v[i].second = b;
			if(b > len)
				len = b;
		}
		sort(v, v+n);
		memset(bit0, 0, sizeof bit0);
		memset(bit1, 0, sizeof bit1);
		ans = 0;
		tot0 = tot1 = 0;
		for(int i=0; i<n; ++i){
			ll num = sum(bit0, v[i].second);
			ll dist = sum(bit1, v[i].second);
			ll t = num*v[i].second-dist;
			t += tot0 - dist - (i-num)*v[i].second;
			ans += t * v[i].first;
//			printf("%lld %lld %lld\n", num, dist, ans);
			add(bit0, v[i].second, 1);
			add(bit1, v[i].second, v[i].second);
			tot0 += v[i].second;
		}
		printf("%lld\n", ans);
	}
	return 0;
}