#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

ll mod_mul(ll a, ll b, ll mod)
{
	a %= mod;
	ll ret = 0;
	while(b){
		if(b & 1)
			ret = (ret+a) % mod;
		a = (a+a) % mod;
		b >>= 1;
	}
	return ret;
}

ll mod_exp(ll a, ll b, ll mod)
{
	a %= mod;
	ll ret = 1;
	while(b){
		if(b & 1)
			ret = mod_mul(ret, a, mod);
		a = mod_mul(a, a, mod);
		b >>= 1;
	}
	return ret;
}

ll gcd(ll a, ll b)
{
	if(a % b == 0)
		return b;
	return gcd(b, a % b);
}

ll llabs(ll x)
{
	return x > 0? x : -x;
}

bool witness(ll a, ll n)
{
	ll u = n-1;
	int t = 0;
	while(u % 2 == 0){
		++t;
		u >>= 1;
	}
	a = mod_exp(a, u, n);
	for(int i=0; i<t; ++i){
		ll pa = mod_mul(a, a, n);
		if(pa==1 && a!=1 && a!=n-1)
			return true;
		a = pa;
	}
	if(a == 1)
		return false;
	return true;
}

bool miller_rabin(ll n, int s)
{
	for(int i=0; i<s; ++i){
		if(witness(rand()%(n-1)+1, n))
			return false;
	}
	return true;
}

bool isPrime(ll n)
{
	if(n>2 && n%2!=0)
		return miller_rabin(n, 20);
	return n == 2;
}

ll pollard_rho(ll n, ll c)
{
	int i = 1;
	ll x = rand() % n;
	ll y = x;
	int k = 2;
	while(1){
		++i;
		x = (mod_mul(x, x, n) + c) % n;
		ll d = gcd(llabs(y-x), n);
		if(d!=1 && d!=n)
			return d;
		if(x == y)
			return n;
		if(k == i){
			y = x;
			k <<= 1;
		}
	}
}

vector<ll> v;

void gao(ll n)
{
	if(n < 2)
		return;
	if(isPrime(n))
		v.push_back(n);
	else{
		ll d = pollard_rho(n,rand()%(n-1)+1);
		gao(d);
		gao(n / d);
	}
}

int main()
{
	srand(time(NULL));
	int t;
	ll x;
	scanf("%d", &t);
	while(t--){
		scanf("%lld", &x);
		v.clear();
		gao(x);
		if(v.size() <= 1)
			puts("Prime");
		else{
			x = v[0];
			for(int i=1; i<(int)v.size(); ++i)
				if(x > v[i])
					x = v[i];
			printf("%lld\n", x);
		}
	}
	return 0;
}