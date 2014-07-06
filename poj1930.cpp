#include <cstdio>
#include <cstring>
#include <cmath>

typedef long long ll;

ll gcd(ll a, ll b)
{
	if(a % b == 0)
		return b;
	return gcd(b, a%b);
}

ll mod_exp(ll a, ll b)
{
	ll ret = 1;
	while(b){
		if(b & 1)
			ret *= a;
		a *= a;
		b >>= 1;
	}
	return ret;
}

int main()
{
	char buf[32];
	gets(buf);
	ll x, y, z;
	ll de, nu;
	while(strlen(buf) > 2){
		int i = 2;
		while(buf[i] != '.')
			++i;
		buf[i] = 0;
		sscanf(buf+2, "%lld", &x);
		z = 10;
		de = -1;
		int len = strlen(buf+2);
		ll exp = mod_exp(10, len);
		for(i=0; i<len; ++i){
			ll a = x*z + x%z - x;
			ll b = (z-1) * exp;
			ll d = gcd(a, b);
			if(de==-1 || b/d<de){
				de = b / d;
				nu = a / d;
			}
			z *= 10;
		}
		printf("%lld/%lld\n", nu, de);
		gets(buf);
	}
	return 0;
}