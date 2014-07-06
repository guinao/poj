#include <cstdio>
#include <algorithm>
using namespace std;

typedef int ll;
const int maxn = 50000;

struct _cow{
	int s, w;
}cow[maxn];

bool cmp(const _cow &c1, const _cow &c2)
{
	return c1.w - c2.s < c2.w - c1.s;
}

int n;

int main()
{
	ll ans, sum;
	int wi, si;
	while(EOF != scanf("%d", &n)){
		for(int i=0; i<n; ++i){
			scanf("%d %d", &wi, &si);
			cow[i].w = wi;
			cow[i].s = si;
		}
		sort(cow, cow+n, cmp);
		sum = 0;
		ans = -999999999;
		for(int i=0; i<n; ++i){
			ans = max(ans, sum-cow[i].s);
			sum += cow[i].w;
		}
		printf("%d\n", ans);
	}
	return 0;
}