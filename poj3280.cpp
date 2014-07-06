#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int inf = 999999999;
const int maxn = 2048;

int dp[maxn][maxn];
int cost[26];

int main()
{
	int n, m;
	int x, y;
	char c, buf[maxn];
	while(EOF != scanf("%d %d", &n, &m)){
		scanf("%s", buf);
		for(int i=0; i<n; ++i){
			getchar();
			scanf("%c %d %d", &c, &x, &y);
			cost[c-'a'] = min(x, y);
		}
		for(int l=1; l<m; ++l){
			for(int i=0; i<m-l; ++i){
				dp[i][i+l] = inf;
				if(buf[i] == buf[i+l])
					dp[i][i+l] = dp[i+1][i+l-1];
				dp[i][i+l] = min(dp[i][i+l], cost[buf[i]-'a']+dp[i+1][i+l]);
				dp[i][i+l] = min(dp[i][i+l], cost[buf[i+l]-'a']+dp[i][i+l-1]);
			}
		}
		printf("%d\n", dp[0][m-1]);
	}
	return 0;
}