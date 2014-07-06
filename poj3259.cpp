#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int maxn = 512;
const int inf = 999999999;

int d[maxn][maxn];

bool spfa(int n)
{
	deque<int> q;
	int p[maxn];
	int cnt[maxn];
	bool visit[maxn];
	memset(p, 0, sizeof p);
	while(!q.empty())
		q.pop_back();
	for(int i=1; i<=n; ++i){
		q.push_back(i);
		visit[i] = true;
		cnt[i] = 1;
	}
	while(!q.empty()){
		int a = q.front();
		q.pop_front();
		for(int i=1; i<=n; ++i){
			if(p[i] > p[a]+d[a][i]){
				p[i] = p[a] + d[a][i];
				if(!visit[i]){
					cnt[i]++;
					if(cnt[i] >= n){
						while(!q.empty())
							q.pop_front();
						return true;
					}
					visit[i] = true;
					if(!q.empty() && p[q.front()] > p[i]){
						q.push_front(i);
					}
					else{
						q.push_back(i);
					}
				}
			}
		}
		visit[a] = false;
	}
	return false;
}

int main()
{
	int f, n, m, w;
	int s, e, t;
	scanf("%d", &f);
	while(f--){
		scanf("%d %d %d", &n, &m, &w);
		for(int i=1; i<=n; ++i){
			fill(d[i], d[i]+n+1, inf);
			d[i][i] = 0;
		}
		for(int i=0; i<m; ++i){
			scanf("%d %d %d", &s, &e, &t);
			if(d[s][e] > t)
				d[s][e] = d[e][s] = t;
		}
		for (int i=0; i<w; ++i)
		{
			scanf("%d %d %d", &s, &e, &t);
			if(d[s][e] > -t)
				d[s][e] = -t;
		}
		if(spfa(n))
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}