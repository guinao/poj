#include <cstdio>
#include <cstring>

const int maxn = 100001;

typedef long long ll;
ll x[maxn], y[maxn], z[maxn];
int n;

bool satisfy(ll d)
{
	ll sum = 0;
	for(int i=0; i<n; ++i){
		if(x[i]<=d && d<=y[i])
			sum += (d-x[i]) / z[i] + 1;
		else if(d > y[i])
			sum += (y[i] - x[i]) / z[i] + 1;
	}
	return sum % 2 == 1;
}

int main()
{
	ll lb, ub;
	bool over = false;
	char buf[64];
	while(!over){
		n = 0;
		lb = ub = 0;
		while(1){
			if(gets(buf) == 0){
				over = true;
				break;
			}
			if(buf[0] == 0)
				break;
			sscanf(buf, "%lld %lld %lld", &x[n], &y[n], &z[n]);
			if(y[n] > ub)
				ub = y[n];
			++n;
		}
		if(n == 0) continue;
		while(ub - lb > 1){
			ll mid = (lb+ub) / 2;
			if(satisfy(mid))
				ub = mid;
			else
				lb = mid;
		}
		int cnt = 0;
		for(int i=0; i<n; ++i){
			if(x[i]<=ub && ub<=y[i]
				&& (ub-x[i])%z[i] == 0)
				++cnt;
		}
		if(cnt % 2 == 1)
			printf("%lld %d\n", ub, cnt);
		else
			puts("no corruption");
	}
	return 0;
}