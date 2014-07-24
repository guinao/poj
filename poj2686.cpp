#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 8;
const int maxm = 32;
const double inf = 999999999;

double dp[1<<maxn][maxm];
int g[maxm][maxm];

double min(double a, double b)
{
	return a < b ? a : b;
}

int main()
{
	int n, m, p, a, b;
	int x, y, z;
	int t[maxn];
	double ans;
	while(EOF != scanf("%d %d %d %d %d", &n, &m, &p, &a, &b)){
		if(!(n || m || p || a || b)) break;
		for(int i=0; i<n; ++i) scanf("%d", t+i);
		memset(g, -1, sizeof g);
		for(int i=0; i<m; ++i)
			g[i][i] = 0;

		for(int i=0; i<p; ++i){
			scanf("%d %d %d", &x, &y, &z);
			g[x-1][y-1] = z;
			g[y-1][x-1] = z;
		}

		for(int i=0; i<1<<n; ++i)
			fill(dp[i], dp[i]+maxm, inf);
		dp[(1<<n)-1][a-1] = 0;
		ans = inf;
		for(int i=(1<<n)-1; i>=0; --i){
			ans = min(ans, dp[i][b-1]);
			for(int j=0; j<n; ++j) if(i>>j & 1){
				for(int u=0; u<m; ++u){
					for(int v=0; v<m; ++v) if(g[u][v]>0){
						dp[i & ~(1<<j)][v] = min(dp[i & ~(1<<j)][v], dp[i][u]+g[u][v]*1./t[j]);
						//printf("%d-->%d:%.3f\n", u+1, v+1, dp[i & ~(1<<j)][v]);
					}
				}
			}
		}
		if(ans < inf)
			printf("%.3f\n", ans);
		else
			puts("Impossible");
	}
	return 0;
}