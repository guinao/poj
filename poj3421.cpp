#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <map>
#include <utility>
#include <vector>
using namespace std;

vector<pair<int,int> > v;

int mod_exp(int a, int b, int n)
{
	int ret = 1;
	a %= n;
	while(b){
		if(b & 1)
			ret = (long long)ret*a % n;
		a = (long long)a * a % n;
		b >>= 1;
	}
	return ret;
}

bool witness(int a, int n)
{
	int u = n-1;
	int t = 0;
	while(u % 2 == 0){
		u >>= 1;
		++t;
	}
	a = mod_exp(a, u, n);
	for(int i=0; i<t; ++i){
		int pa = (long long)a * a % n;
		if(pa==1 && a!=1 && a!=n-1)
			return true;
		a = pa;
	}
	if(a != 1)
		return true;
	return false;
}

bool miller_rabin(int n ,int s)
{
	for(int i=0; i<s; ++i)
		if(witness(rand()%(n-1)+1, n))
			return false;
	return true;
}

bool isPrime(int n)
{
	if(n>2 && n%2==1)
		return miller_rabin(n, 20);
	return n == 2;
}

void gao(int n)
{
	for(int i=2; i*i<=n; ++i){
		int cnt = 0;
		while(n%i == 0){
			++cnt;
			n /= i;
		}
		v.push_back(make_pair(i, cnt));
	}
	if(n != 1)
		v.push_back(make_pair(n ,1));
}

long long fact(int n)
{
	long long ret = 1;
	for(int i=2; i<=n; ++i)
		ret *= i;
	return ret;
}

int main()
{
	int x;
	int dp[2][32];
	while(EOF != scanf("%d", &x)){
		v.clear();
		gao(x);
		memset(dp, 0, sizeof dp);
		int cnt = 0;
		long long divisor = 1;
		for(int i=0; i<(int)v.size(); ++i){
			cnt += v[i].second;
			divisor *= fact(v[i].second);
		}
		printf("%d %d\n", cnt, (int)(fact(cnt)/divisor));
	}

	return 0;
}