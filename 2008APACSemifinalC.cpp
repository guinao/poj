#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

double dp[2][1<<15|1];

int main()
{
	freopen("F:\\Downloads\\C-large-practice.in", "r", stdin);
	freopen("large.out", "w", stdout);
	int n, m, x;
	double p;
	scanf("%d", &n);
	for(int re=1; re<=n; ++re){
		scanf("%d %lf %d", &m, &p, &x);
		dp[0][0] = 0.0;
		dp[0][1] = 1.0;
		for(int r=1, i=2; r<=m; ++r, i*=2){
			dp[r%2][0] = 0.0;
			dp[r%2][i] = 1.0;
			for(int j=1; j<i; ++j){
				int l = min(j, i-j);
				dp[r%2][j] = 0.0;
				for(int k=0; k<=l; ++k){
					double v = dp[(r-1)%2][(j-k)>>1]*(1-p) + dp[(r-1)%2][(j+k)>>1]*p;
					dp[r%2][j] = max(v, dp[r%2][j]);
				}
			}
		}
		double index = x * 1. / 1000000 * (1<<m);
		printf("Case #%d: %.6f\n", re, dp[m%2][(int)index]);
	}
	return 0;
}