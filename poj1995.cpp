#include <cstdio>

typedef int ll;

ll mod_mul(ll a, ll b, ll n)
{
	ll ret = 0;
	a %= n;
	while(b){
		if(b & 1)
			ret = (a + ret) % n;
		a = (a+a)% n;
		b >>= 1;
	}
	return ret;
}

ll mod_exp(ll a, ll b, ll n)
{
	ll ret = 1;
	a %= n;
	while(b){
		if(b & 1)
			ret = (long long)a*ret % n;
		a = (long long)a * a % n;
		b >>= 1;
	}
	return ret;
}

int main()
{
	int z, n;
	ll m, a, b;
	scanf("%d", &z);
	while(z--){
		scanf("%d", &m);
		scanf("%d", &n);
		ll ans = 0;
		for(int i=0; i<n; ++i){
			scanf("%d %d", &a, &b);
			ans = (ans+mod_exp(a, b, m)) % m;
		}
		printf("%d\n", ans);
	}
}