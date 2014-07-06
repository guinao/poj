#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

typedef long long ll;

ll aa(ll a)
{
	return a >= 0 ? a : -a;
}

ll mod_mul(ll a, ll b, ll mod)
{
	ll ret = 0;
	a %= mod;
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
	ll ret = 1;
	a %= mod;
	while(b){
		if(b & 1)
			ret = mod_mul(ret, a, mod);
		a = mod_mul(a, a, mod);
		b >>= 1;
	}
	return ret;
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
	for(int i=1; i<=t; ++i){
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
	srand(time(NULL));
	for(int i=0; i<s; ++i){
		ll x = rand()%(n-1) + 1;
		if(witness(x, n))
			return false;
	}
	return true;
}

bool isPrime(ll n)
{
	if(n>2 && n%2 != 0){
		return miller_rabin(n, 50);
	}
	return n == 2;
}

ll extend_eculid(ll &a, ll x, ll &b, ll y)
{
	ll c = x / y;
	ll z = x % y;
	if(z == 0){
		a = 0;
		b = 1;
		return y;
	}
	else{
		ll aa, bb;
		ll d = extend_eculid(aa, y, bb, z);
		a = bb;
		b = aa - bb * c;
		return d;
	}
}

ll gcd(ll a, ll b)
{
	if(a % b == 0)
		return b;
	return gcd(b, a%b);
}

ll pollard_rho(ll n, ll c)
{
	if(n % 2 == 0)
		return 2;
	int i = 1;
	srand(time(NULL));
	ll x = rand() % n;
	ll y = x;
	int k = 2;
	while(1){
		++i;
		x = (mod_mul(x, x, n) + c) % n;
		ll ta, tb;
		ll p = extend_eculid(ta, aa(y-x), tb, n);
		if(p!=1 && p!=n)
			return p;
		if(y == x)
			return n;
		if(k == i){
			y = x;
			k <<= 1;
		}
	}
}

vector<ll> v;
pair<ll, ll> ans;

void gao(ll n)
{
	if(n <= 1)
		return ;
	if(!isPrime(n)){
		ll d = pollard_rho(n, rand()%(n-1)+1);
		n /= d;
		gao(n);
		gao(d);
	}
	else
		v.push_back(n);
}

void dfs(ll a, ll b, int index)
{
	if(a + b >= ans.first+ans.second)
		return ;
	if(index >= (int)v.size()){
		ans.first = min(a, b);
		ans.second = max(a, b);
	}
	else{
		dfs(a*v[index], b, index+1);
		dfs(a, b*v[index], index+1);
	}
}

int main()
{
	ll a, b;
	while(EOF != scanf("%lld %lld", &a, &b)){
		b /= a;
		v.clear();
		ans.first = b;
		ans.second = b;
		gao(b);
		sort(v.begin(), v.end());
		vector<ll> v2;
		ll t = 1, tt = 1;
		for(int i=0; i<(int)v.size(); ++i){
			if(tt != v[i]){
				v2.push_back(t);
				tt = t = v[i];
			}
			else{
				t *= v[i];
			}
		}
		v2.push_back(t);
		v = v2;
		dfs(1, 1, 0);
		printf("%lld %lld\n", ans.first*a, ans.second*a);
	}
	return 0;
}