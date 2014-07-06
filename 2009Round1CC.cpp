#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define inf 999999999

int pos[128];
int dp[128][128];

int main()
{
	freopen("F:\\Downloads\\C-large-practice.in", "r", stdin);
	freopen("large.out", "w", stdout);
	int t, p, q;
	scanf("%d", &t);
	for(int re=1; re<=t; ++re){
		scanf("%d %d", &p, &q);
		pos[0] = 0;
		pos[q+1] = p+1;
		for(int i=1; i<=q; ++i){
			scanf("%d", pos+i);
		}
		for(int i=0; i<=q+1; ++i){
			dp[i][i] = 0;
		}
		sort(pos, pos+q+2);
		memset(dp, 0, sizeof dp);
		for(int l=2; l<=q+1; ++l){
			for(int s=0; s+l<=q+1; ++s){
				dp[s][s+l] = inf;
				for(int i=s+1; i<s+l; ++i){
					dp[s][s+l] = min(dp[s][i]+dp[i][s+l], dp[s][s+l]);
				}
				dp[s][s+l] += pos[s+l] - pos[s] - 2;
			}
		}
		printf("Case #%d: %d\n", re, dp[0][q+1]);
	}
	return 0;
}