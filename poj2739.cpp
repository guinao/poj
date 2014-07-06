#include <cstdio>
#include <vector>
#include <cstdlib>
using namespace std;

int mod_mul(int a, int b, int n)
{
	int res = 0;
	a %= n;
	while(b){
		if(b & 1)
			res = (res + a) % n;
		a = (a + a) % n;
		b >>= 1;
	}
	return res;
}

int mod_exp(int a, int b, int n)
{
	int res = 1;
	a %= n;
	while(b){
		if(b & 1)
			res = mod_mul(res, a, n);
		a = mod_mul(a, a, n);
		b >>= 1;
	}
	return res;
}

bool witness(int x, int n)
{
	int a = n-1;
	int t = 0;
	while(a % 2 == 0){
		++t;
		a /= 2;
	}
	x = mod_exp(x, a, n);
	for(int i=1; i<=t; ++i){
		int px = mod_mul(x, x, n);
		if(px==1 && x!=1 && x!=n-1)
			return true;
		x = px;
	}
	if(x == 1)
		return false;
	return true;
}

bool miller_rabin(int n, int s)
{
	for(int i=0; i<s; ++i){
		if(witness(rand()%(n-1)+1, n))
			return false;
	}
	return true;
}

bool isPrime(int x)
{
	if(x > 2 && x%2==1)
		return miller_rabin(x, 20);
	return x == 2;
}

int main()
{
	vector<int> p;
	int n;
	p.clear();
	srand(0);
	for(int i=2; i<=10000; ++i){
		if(isPrime(i))
			p.push_back(i);
	}
	while(EOF != scanf("%d", &n)){
		if(n == 0) break;
		int l = 0, u = 0;
		int sum = 0, ans = 0;
		while(p[l] <= n){
			while(sum < n)
				sum += p[u++];
			if(sum == n)
				++ans;
			sum -= p[l++];
		}
		printf("%d\n", ans);
	}
	return 0;
}