#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
using namespace std;

const int maxn = 16;
const int inf = 999999999;

int dp[2<<maxn];

int main()
{
	int n, x, y;
	pair<int,int> p[maxn];
	while(EOF != scanf("%d", &n)){
		if(n == 0) break;
		for(int i=0; i<n; ++i){
			scanf("%d %d", &x, &y);
			p[i].first = x;
			p[i].second = y;
		}
		fill(dp, dp+(1<<n), inf);
		dp[0] = 0;
		for(int i=0; i<n; ++i){
			for(int j=i+1; j<n; ++j){
				int x1 = min(p[i].first, p[j].first);
				int x2 = max(p[i].first, p[j].first);
				int y1 = min(p[i].second, p[j].second);
				int y2 = max(p[i].second, p[j].second);
				int t = 0;
				for(int k=0; k<n; ++k){
					if(x1<=p[k].first && p[k].first<=x2 && y1<=p[k].second && p[k].second<=y2)
						t |= 1<<k;
				}
				int rect = (x2-x1) * (y2-y1);
				if(x1 == x2)
					rect = y2 - y1;
				else if(y1 == y2)
					rect = x2 - x1;
				for(int s=(1<<n)-1; s>=0; --s)
					dp[s|t] = min(dp[s|t], dp[s]+rect);
			}
		}
		printf("%d\n", dp[(1<<n)-1]);
	}
	return 0;
}