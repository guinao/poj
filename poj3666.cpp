#include<cstdio>
#include<utility>
#include<algorithm>
using namespace std;

const int maxn = 2048;

int dp[2][maxn];
int a[maxn];

int gao(int n)
{
	int ret;
	int b[maxn];
	for(int i=0; i<n; ++i){
		b[i] = a[i];
	}
	sort(b, b+n);
	memset(dp, 0, sizeof dp);
	for(int i=0,k=0; i<n; ++i){
		dp[k][0] = dp[1-k][0] + abs(a[i]-b[0]);
		for(int j=1; j<n; ++j){
			dp[k][j] = min(dp[k][j-1], dp[1-k][j]+abs(a[i]-b[j]));
		}
		k = 1-k;
	}
	ret = dp[(n-1)%2][0];
	for(int i=1; i<n; ++i){
		if(dp[(n-1)%2][i] < ret)
			ret = dp[(n-1)%2][i];
	}
	return ret;
}

int main()
{
	int n;
	int ans;
	while(EOF != scanf("%d", &n)){
		for(int i=0; i<n; ++i){
			scanf("%d", &a[i]);
		}
		ans = gao(n);
		for(int i=0; i<n; ++i){
			a[i] = -a[i];
		}
		ans = min(ans, gao(n));
		printf("%d\n", ans);
	}
	return 0;
}