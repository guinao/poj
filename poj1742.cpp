#include<cstdio>
#include<cstring>
#define min(a,b) (a)<(b)?(a):(b)
const int maxn = 100010;

int dp[maxn];
bool mark[maxn];

int main()
{
	int n, m, ans;
	int a[1024], c[1024];
	scanf("%d %d", &n, &m);
	while(n!=0 && m!=0){
		memset(dp, 0, sizeof(int)*(m+1));
		memset(mark, 0, sizeof mark);
		for(int i=0; i<n; ++i)
			scanf("%d", a+i);
		for(int i=0; i<n; ++i)
			scanf("%d", c+i);
		mark[0] = true;
		for(int i=0; i<n; ++i){
			for(int j=0; j<=m-a[i]; ++j){
				dp[j] = mark[j] ? c[i] : 0;
			}
			for(int j=a[i]; j<=m; ++j){
				if(!mark[j] && dp[j-a[i]]>0){
					mark[j] = true;
					dp[j] = dp[j-a[i]] - 1;
				}
			}
		}
		ans = 0;
		for(int i=1; i<=m; ++i)
			if(mark[i])
				++ans;
		printf("%d\n", ans);
		scanf("%d %d", &n, &m);
	}
	return 0;
}