#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int inf = 999999999;

int dp[40010];

int main()
{
	int n;
	int p, t;
	scanf("%d", &n);
	for(int re=0; re<n; ++re){
		scanf("%d", &p);
		fill(dp, dp+p, inf);
		for(int i=0; i<p; ++i){
			scanf("%d", &t);
			*lower_bound(dp, dp+i+1, t) = t;
		}
		for(t=0; t<p; ++t){
			if(dp[t] == inf)
				break;
		}
		printf("%d\n", t);
	}
	return 0;
}