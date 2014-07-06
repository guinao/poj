#include<cstdio>

const int mod = 1000000000;

int dp[1<<20];

int main()
{
	int n;
	scanf("%d", &n);
	for(int i=0; i<=n; ++i){
		dp[i] = 1;
	}
	for(int j=2; j<=n; j=j<<1){
		for(int i=j; i<=n; ++i){
			dp[i] += dp[i-j];
			if(dp[i] > mod)
				dp[i] -= mod;
		}
	}
	printf("%d\n", dp[n]);
	return 0;
}