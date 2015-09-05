#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
using namespace std;

const int inf = 999999999;
const int maxn = 16;
int dp[maxn][1<<maxn];
int mem[maxn][1<<maxn];
int pre[maxn][maxn];
char dna[maxn][128];
int n, ca;

string dfs(int val, int j, int s)
{
	s &= ~(1<<j);
	if(s == 0)
		return string(dna[j]);

	string ret = "ZZZ";
	int index = -1;
	for(int i=0; i<n; ++i) if(s & 1<<i){
		if(val == dp[i][s]+pre[i][j]){
			string tmp = dfs(dp[i][s], i, s);
			if(index==-1 || ret>tmp){
				ret = tmp;
				index = i;
			}
		}
	}

	int k = strlen(dna[j]) - pre[index][j];
	ret += string(dna[j]+k);

	return ret;
}

int main()
{
//	freopen("poj1795.out", "w", stdout);
	scanf("%d", &ca);
	for(int re=1; re<=ca; ++re){
		scanf("%d", &n);
		memset(pre, 0, sizeof pre);
		for(int i=0; i<n; ++i){
			scanf("%s", dna[i]);
			for(int j=0; j<i; ++j){
				int la = strlen(dna[i]);
				int lb = strlen(dna[j]);
				for(int k=0; k<=la; ++k){
					if(0 == strncmp(dna[i]+k, dna[j], min(la-k, lb))){
						pre[i][j] = max(0, lb+k-la);
						break;
					}
				}
				for(int k=0; k<=lb; ++k){
					if(0 == strncmp(dna[j]+k, dna[i], min(lb-k, la))){
						pre[j][i] = max(0, la+k-lb);
						break;
					}
				}
			}
		}

		for(int i=0; i<n; ++i){
			fill(dp[i], dp[i]+(1<<n), inf);
			dp[i][1<<i] = strlen(dna[i]);
		}
		memset(mem, -1, sizeof mem);
		for(int s=0; s<1<<n; ++s){
			for(int i=0; i<n; ++i) if(!(s&1<<i)){
				int val = dp[i][s|1<<i];
				int index = -1;
				for(int j=0; j<n; ++j){
					if(s & 1<<j){
						val = min(val, dp[j][s] + pre[j][i]);
					}
				}
				dp[i][s|1<<i] = val;
			}
		}

		printf("Scenario #%d:\n", re);
		string ans = "ZZZ";
		int val = inf;
		int s = (1<<n) - 1;
		for(int i=0; i<n; ++i)
			val = min(val, dp[i][s]);
//		printf("%d\n\n", val);
		for(int i=0; i<n; ++i){
			if(val == dp[i][s]){
				ans = min(ans, dfs(val, i, s));
			}
		}

		printf("%s\n\n", ans.c_str());
	}
	return 0;
}