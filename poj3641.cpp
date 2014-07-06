#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

typedef int ll;

ll mod_mul(ll a, ll b, ll n)
{
	ll ret = 0;
	a %= n;
	while(b){
		if(b & 1)
			ret = (ret+a) % n;
		a = (a+a) % n;
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
			ret = mod_mul(ret, a, n);
		a = mod_mul(a, a, n);
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
	for(int i=0; i<t; ++i){
		ll pa = mod_mul(a, a, n);
		if(pa==1 && a!=1 && a!=n-1)
			return true;
		a = pa;
	}
	if(a != 1)
		return true;
	return false;
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

int main()
{
	ll a, p;
	while(EOF != scanf("%d %d", &p, &a)){
		if(p==0 && a==0)
			break;
		if(!isPrime(p) && (mod_exp(a, p, p) == a%p))
			puts("yes");
		else
			puts("no");
	}
	return 0;
}