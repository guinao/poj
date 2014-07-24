#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;

const int maxn = 16;
const int inf = 999999999;

struct edge{
	int to, c, p, r;
};

vector<edge> roads[maxn];
int dp[maxn][1<<maxn];
bool mark[maxn][1<<maxn];

void spfa()
{
	dp[0][1] = 0;
	deque<pair<int,int> > q;
	q.push_front(make_pair(0, 1));
	while(!q.empty()){
		int c = q.front().first;
		int s = q.front().second;
		q.pop_front();
		mark[c][s] = false;
		for(int i=0; i<(int)roads[c].size(); ++i){
			edge &e = roads[c][i];
			int val = e.r;
			if(s & 1<<e.c)
				val = min(val, e.p);
			if(dp[e.to][s|1<<e.to] > dp[c][s]+val){
				dp[e.to][s|1<<e.to] = dp[c][s]+val;
//				printf("%d %d %d\n", e.to, s|1<<e.to, dp[e.to][s|1<<e.to]);
				if(!mark[e.to][s|1<<e.to]){
					mark[e.to][s|1<<e.to] = true;
					q.push_back(make_pair(e.to, s|1<<e.to));
				}
			}
		}
	}
}

int main()
{
	int n, m;
	int a, b, c, p, r;
	edge e;
	while(EOF != scanf("%d %d", &n, &m)){
		for(int i=0; i<n; ++i)
			roads[i].clear();
		for(int i=0; i<m; ++i){
			scanf("%d %d %d %d %d", &a, &b, &c, &p, &r);
			e.c = c-1;
			e.p = p;
			e.r = r;
			e.to = b-1;
			roads[a-1].push_back(e);
		}

		for(int i=0; i<n; ++i){
			fill(dp[i], dp[i]+(1<<n), inf);
		}
		memset(mark, 0, sizeof mark);
		spfa();

		int ans = inf;
		for(int s=1<<(n-1); s<1<<n; ++s){
			ans = min(ans, dp[n-1][s]);
		}
		if(ans < inf)
			printf("%d\n", ans);
		else
			puts("impossible");
	}
	return 0;
}