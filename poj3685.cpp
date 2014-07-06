#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;
const ll inf = 10000000000LL;
ll n, m;

bool satisfy(ll d)
{
	ll sum = 0;
	for(ll j=1; j<=n; ++j){
		double c = j*j - 100000*j - d;
		double delta = (100000+j)*(100000+j) - 4*c;
		double root = (-(100000+j) + sqrt(delta)) / 2.0;
		if(root > 0)
			sum += min((ll)floor(root), n);
	}
	return sum < m;
}

int main()
{
	ll ub, lb, mid;
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%lld %lld", &n, &m);
		ub = inf;
		lb = -inf;
		while(ub - lb > 1){
			mid = (lb + ub) / 2;
			if(satisfy(mid))
				lb = mid;
			else
				ub = mid;
		}
		printf("%lld\n", ub);
	}
	return 0;
}