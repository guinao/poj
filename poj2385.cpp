#include<cstdio>
#include<cstring>

int min(int a, int b)
{
	return a<b? a : b;
}

int main()
{
	int w, t, x;
	int dp[32];
	while(EOF != scanf("%d %d", &t, &w)){
		memset(dp, 0, sizeof dp);
		for(int i=1; i<=t; ++i){
			scanf("%d", &x);
			for(int j=min(w, i); j>=0; --j){
				if(x-1 == j%2)
					dp[j]++;
				else if(j-1>=0 && dp[j-1]+1>dp[j])
					dp[j] = dp[j-1]+1;	
			}
		}
		printf("%d\n", dp[w]);
	}
	return 0;
}