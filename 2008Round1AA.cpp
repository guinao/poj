#include<cstdio>
#include<algorithm>
using namespace std;

int main()
{
	freopen("A-large-practice.in", "r", stdin);
	freopen("large.out", "w", stdout);
	int t, n;
	int x[1024], y[1024];
	long long ans;
	scanf("%d", &t);
	for(int re=1; re<=t; ++re){
		scanf("%d", &n);
		for(int i=0; i<n; ++i)
			scanf("%d", x+i);
		for(int i=0; i<n; ++i)
			scanf("%d", y+i);
		sort(x, x+n);
		sort(y, y+n);
		ans = 0;
		for(int i=0; i<n; ++i)
			ans += (long long)x[i] * y[n-i-1];
		printf("Case #%d: %lld\n", re, ans);
	}
	return 0;
}