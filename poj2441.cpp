#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int maxn = 20;

int dp[1<<maxn];
vector<int> p[maxn];

int main()
{
	int n, m;
	int x, y, z;
	while(EOF != scanf("%d %d", &n, &m)){
		for(int i=0; i<n; ++i){
			scanf("%d", &x);
			p[i].clear();
			while(x--){
				scanf("%d", &y);
				p[i].push_back(y-1);
			}
		}
		if(n > m){
			puts("0");
			continue;
		}
		memset(dp, 0, sizeof dp);
		dp[(1<<m)-1] = 1;
		for(int i=0; i<n; ++i){
			for(int s=0; s<1<<m; ++s){
				if(dp[s] != 0){
					for(int j=0; j<(int)p[i].size(); ++j){
						int k = p[i][j];
						if(s>>k & 1){
							dp[s & ~(1<<k)] += dp[s];
						}
					}
				}
				dp[s] = 0;
			}
		}

		int ans = 0;
		for(int s=0; s<1<<m; ++s){
			ans += dp[s];
		}
		printf("%d\n", ans);
	}
	return 0;
}