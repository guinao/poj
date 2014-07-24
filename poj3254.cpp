#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 12;
const int mod = 100000000;

int dp[2][1<<maxn];
int f[maxn][maxn];

int main()
{
	int m, n;
	int *crt, *next;
	while(EOF != scanf("%d %d", &m, &n)){
		for(int i=0; i<m; ++i){
			for(int j=0; j<n; ++j){
				scanf("%d", &f[i][j]);
			}
		}

		memset(dp, 0, sizeof dp);
		crt = dp[0];
		next = dp[1];
		crt[0] = 1;
		for(int i=0; i<m; ++i){
			for(int j=0; j<n; ++j){
				for(int s=0; s<1<<n; ++s){
					if(f[i][j] == 0){
						if(s & 1<<j)
							next[s] = 0;
						else
							next[s] = crt[s] + crt[s | (1<<j)];
					}else{
						if(s & 1<<j){
							if(j>0 && (s&1<<(j-1)))
								next[s] = 0;
							else
								next[s] = crt[s & ~(1<<j)];
						}else{
							next[s] = crt[s] + crt[s|(1<<j)];
						}
					}
					next[s] %= mod;
				}
				swap(crt, next);
			}
		}
		int ans = 0;
		for(int i=0; i<1<<n; ++i)
			ans = (ans+crt[i]) % mod;
		printf("%d\n", ans);
	}
	return 0;
}