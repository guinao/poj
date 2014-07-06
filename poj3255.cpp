#include<cstdio>
#include<cstring>
#include<vector>
#include<utility>
#include<queue>
#include<algorithm>
using namespace std;

const int maxv = 5010;
const int maxe = 100010;
const int inf = 999999999;

typedef pair<int,int> P;	//to, weight

vector<P> path[maxv];

int dijkstra(int n){
	int fir[maxv];
	int sec[maxv];
	fill(fir, fir+maxv, inf);
	fill(sec, sec+maxv, inf);
	priority_queue<P, vector<P>, greater<P> > q;
	q.push(make_pair(0, 1));
	while(!q.empty()){
		int u = q.top().second;
		int d = q.top().first;
		q.pop();
		if(sec[u] < d) continue;
		for(int i=0; i<(int)path[u].size(); ++i){
			int v = path[u][i].first;
			int cost = path[u][i].second;
			if(fir[v] > d + cost){
				sec[v] = fir[v];
				fir[v] = d + cost;
				q.push(make_pair(fir[v], v));
				q.push(make_pair(sec[v], v));
			}else if(sec[v] > d + cost){
				sec[v] = d + cost;
				q.push(make_pair(sec[v], v));
			}
		}
	}
	return sec[n];
}

int main()
{
	int n, r;
	int x, y, z;
	scanf("%d %d", &n, &r);
	for(int i=0; i<r; ++i){
		scanf("%d %d %d", &x, &y, &z);
		path[x].push_back(P(y, z));
		path[y].push_back(P(x, z));
	}
	printf("%d\n", dijkstra(n));
	return 0;
}