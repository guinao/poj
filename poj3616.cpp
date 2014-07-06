#include<cstdio>
#include<cstring>
#include<algorithm>
#include<utility>
using namespace std;

int dp[1<<20];

struct interval{
	int s, t;
	int e;
};

bool cmp(const interval& p1, const interval &p2)
{
	return p1.t < p2.t;
}

int main()
{
	int n, m ,r;
	int x, y, z;
	interval t[1024];
	while(EOF != scanf("%d %d %d", &n, &m, &r)){
		memset(dp, 0, sizeof dp);
		for(int i=0; i<m; ++i){
			scanf("%d %d %d", &x, &y, &z);
			t[i].s = x+1;
			t[i].t = y+1;
			t[i].e = z;
		}
		sort(t, t+m, cmp);
		for(int i=0, j=1; j<=n+1; ++j){
			dp[j] = dp[j-1];
			while(i<m && t[i].t == j){
				x = max(0, t[i].s-r);
				dp[j] = max(dp[j], dp[x]+t[i].e);
				++i;
			}
		}
		printf("%d\n", dp[n+1]);
	}
	return 0;
}