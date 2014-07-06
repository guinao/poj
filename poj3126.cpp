#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int mod_exp(int a, int b, int n)
{
	int ret = 1;
	a %= n;
	while(b){
		if(b & 1)
			ret = (ret*a) % n;
		a = (a*a) % n;
		b >>= 1;
	}
	return ret;
}

bool witness(int a, int n)
{
	int u = n-1;
	int t = 0;
	while(u % 2 == 0){
		++t;
		u >>= 1;
	}
	a = mod_exp(a, u, n);
	for(int i=0; i<t; ++i){
		int pa = (a*a) % n;
		if(pa==1 && a!=1 && a!=n-1)
			return true;
		a = pa;
	}
	if(a == 1)
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

bool isPrime(int n)
{
	if(n>2 && n%2!=0)
		return miller_rabin(n, 20);
	return n == 2;
}

bool visit[10000];
bool prime[10000];

int main()
{
	srand(time(NULL));
	int t;
	int x, y, z;
	int ans;
	vector<int> p;
	queue<pair<int, int> > q;
	p.clear();
	for(int i=1000; i<10000; ++i){
		prime[i] = isPrime(i);
	}

	scanf("%d", &t);
	for(int re=0; re<t; ++re){
		scanf("%d %d", &x, &y);
		memset(visit, 0, sizeof visit);
		while(!q.empty())
			q.pop();
		q.push(make_pair(x, 0));
		visit[x] = true;
		ans = -1;
		while(!q.empty()){
			pair<int, int> cur = q.front();
			q.pop();
			if(cur.first == y){
				ans = cur.second;
				break;
			}
			for(int i=1; i<10000; i*=10){
				for(int j=0; j<10; ++j){
					int next = (cur.first/i/10*10+j)*i+cur.first%i;
					if(prime[next] && !visit[next]){
						q.push(make_pair(next, cur.second+1));
						visit[next] = true;
					}
				}
			}
		}
		if(ans >= 0)
			printf("%d\n", ans);
		else
			puts("Impossible");
	}
	return 0;
}