#include<cstdio>
#include<cstring>

int dp[2][1024000];

const int mod = 1000000;

int main()
{
	int t, a, s, b;
	int f[1024], x, y;
	int cnt, ans;
	while(EOF != scanf("%d %d %d %d", &t, &a, &s, &b)){
		memset(f, 0, sizeof f);
		for(int i=0; i<a; ++i){
			scanf("%d", &x);
			f[x]++;
		}
		memset(dp, 0, sizeof dp);
		dp[0][0] = dp[1][0] = 1;
		for(int i=1; i<=t; ++i){
			int n = (i-1)%2;
			int np = i%2;
			for(int j=1; j<=b; ++j){
				if(j-f[i] > 0){
					dp[np][j] = (dp[np][j-1] + dp[n][j] - dp[n][j-f[i]-1] + mod) % mod;
				}
				else{
					dp[np][j] = (dp[np][j-1] +dp[n][j]) % mod;
				}
				//printf("%d ", dp[np][j]);
			}
			//printf("\n");
		}
		ans = 0;
		for(int i=s; i<=b; ++i){
			ans = (ans+dp[t%2][i])%mod;
		}
		ans = (ans + mod) % mod;
		printf("%d\n", ans);
	}
	return 0;
}