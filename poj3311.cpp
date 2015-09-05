#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 16;
const int inf = 999999999;

int mat[maxn][maxn];
int dp[maxn][1<<maxn];

int min(int a, int b)
{
	return a < b ? a : b;
}

void floyd(int n)
{
	for(int k=0; k<n; ++k)
		for(int i=0; i<n; ++i)
			for(int j=0; j<n; ++j)
				mat[i][j] = min(mat[i][j], mat[i][k]+mat[k][j]);
}

int main()
{
	int n;

	while(EOF != scanf("%d", &n)){
		if(!n) break;

		for(int i=0; i<=n; ++i){
			for(int j=0; j<=n; ++j)
				scanf("%d", &mat[i][j]);
		}

		floyd(n+1);

		for(int i=0; i<=n; ++i)
			fill(dp[i], dp[i]+(1<<n), inf);

		dp[0][0] = 0;

		for(int s=0; s<1<<n; ++s){
			for(int j=0; j<=n; ++j){
				if(dp[j][s] < inf){
					for(int i=1; i<=n; ++i){
						int p = 1<<(i-1);
						if((s&p) == 0){
							dp[i][s|p] = min(dp[i][s|p], dp[j][s]+mat[j][i]);
						}
					}
				}
			}
		}

		int ans = inf;
		int s = (1<<n)-1;
		for(int i=1; i<=n; ++i){
			ans = min(ans, dp[i][s]+mat[i][0]);
		}

		printf("%d\n", ans);
	}

	return 0;
}