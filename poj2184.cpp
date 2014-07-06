#include<cstdio>
#include<cstring>
#include<cassert>
#include<algorithm>
using namespace std;

int inf = 999999999;
const int maxv = 100000;
const int maxn = 128;

int dp[maxv];

int main()
{
	int n, f, s;
	while(EOF != scanf("%d", &n)){
		fill(dp, dp+maxv, -inf);
		dp[maxv / 2] = 0;
		int high = maxv / 2;
		int low = maxn / 2;
		for(int i=0; i<n; ++i){
			scanf("%d %d", &s, &f);
			if(s >= 0){
				for(int j=high; j>=low; --j){
					if(dp[j] != -inf)
						dp[j+s] = max(dp[j+s], dp[j]+f);
				}
				high += s;
				if(high >= maxv)
					high = maxv - 1;
			}
			else{
				for(int j=low; j<=high; ++j){
					if(dp[j] != -inf)
						dp[j+s] = max(dp[j+s], dp[j]+f);
				}
				low += s;
				if(low < 0)
					low = 0;
			}
		}
		int ans = maxv/2;
		for(int i=maxv/2; i<=high; ++i){
			if(dp[i] >= 0)
				ans = max(ans, dp[i]+i);
		}
		printf("%d\n", ans-maxv/2);
	}
	return 0;
}