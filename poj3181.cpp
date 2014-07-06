#include<cstdio>
#include<cstring>

long long dp[128][1024][2];
long long mod = 1000000000000000000LL;

int main()
{
	int n, k;
	while(EOF != scanf("%d %d", &n, &k)){
		dp[0][0][0] = 1;
		dp[0][0][1] = 0;
		for(int i=1; i<=k; ++i){
			for(int j=0; j<=n; ++j){
				dp[i][j][0] = dp[i][j][1] = 0;
				for(int l=0; l<=j; l+=i){
					dp[i][j][0] += dp[i-1][j-l][0];
					dp[i][j][1] += dp[i-1][j-l][1];
					if(dp[i][j][0] >= mod){
						dp[i][j][0] -= mod;
						dp[i][j][1] ++;
					}
				}
			}
		}
		if(dp[k][n][1] != 0){
			printf("%lld%015lld\n", dp[k][n][1], dp[k][n][0]);
		}
		else{
			printf("%lld\n", dp[k][n][0]);
		}
	}
	return 0;
}