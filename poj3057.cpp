#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

const int maxv = 5000;
const int maxn = 16;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int X, Y, V;

vector<int> G[maxv];
int match[maxv];
bool used[maxv];
bool visit[maxn][maxn];
int dist[maxn*4][maxn][maxn];
char buf[maxn][maxn];

void add_edge(int u, int v)
{
	G[u].push_back(v);
	G[v].push_back(u);
}

bool dfs(int v)
{
	used[v] = true;
	for(int i=0; i<G[v].size(); ++i){
		int u = G[v][i], w = match[u];
		if(w==-1 || !used[w]&&dfs(w)){
			match[u] = v;
			match[v] = u;
			return true;
		}
	}
	return false;
}

void cal_dist(int index, int x, int y)
{
	queue<pair<int,int> > que;
	dist[index][x][y] = 0;
	que.push(make_pair(x, y));
	while(!que.empty()){
		x = que.front().first;
		y = que.front().second;
		que.pop();
		for(int i=0; i<4; ++i){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(0<=nx && nx<X && 0<=ny && ny<Y){
				if(buf[nx][ny] == '.' && dist[index][nx][ny]==-1){
					dist[index][nx][ny] = dist[index][x][y] + 1;
					visit[nx][ny] = true;
					que.push(make_pair(nx, ny));
				}
			}
		}
	}
}

int main()
{
	int ca;
	int x, y, d;
	vector<pair<int,int> > doors;
	bool legal;
	scanf("%d", &ca);
	while(ca--){
		scanf("%d %d", &x, &y);
		X = x, Y = y;
		for(int i=0; i<x; ++i)
			scanf("%s", buf[i]);

		doors.clear();
		for(int i=0; i<x; ++i){
			if(buf[i][0] == 'D')
				doors.push_back(make_pair(i, 0));
			if(buf[i][y-1] == 'D')
				doors.push_back(make_pair(i, y-1));
		}
		for(int i=0; i<y; ++i){
			if(buf[0][i] == 'D')
				doors.push_back(make_pair(0, i));
			if(buf[x-1][i] == 'D')
				doors.push_back(make_pair(x-1, i));
		}

		memset(dist, -1, sizeof dist);
		memset(visit, 0, sizeof visit);
		d = doors.size();
		for(int i=0; i<d; ++i){
			cal_dist(i, doors[i].first, doors[i].second);
		}

		legal = true;
		for(int i=0; i<x; ++i) for(int j=0; j<y; ++j){
			if(buf[i][j] == '.' && !visit[i][j]){
				legal = false;
				break;
			}
		}

		if(legal){
			for(int i=0; i<maxv; ++i)
				G[i].clear();
			int t = 0, cnt = 0;
			for(int i=0; i<X; ++i) for(int j=0; j<Y; ++j){
				if(buf[i][j] == '.')
					++cnt;
			}
			int res = 0;
			memset(match, -1, sizeof match);
			while(res < cnt){
				++t;
				for(int i=0; i<d; ++i){
					for(int j=0; j<X; ++j) for(int k=0; k<Y; ++k){
						if(0<dist[i][j][k] && dist[i][j][k]<=t)
							add_edge(j*Y+k, X*Y+(t-1)*d+i);
					}
				}
				for(int i=0; i<X*Y; ++i){
					if(match[i] < 0){
						memset(used, 0, sizeof used);
						if(dfs(i))
							++res;
					}
				}
			}
			printf("%d\n", t);
		}else{
			printf("impossible\n");
		}
	}
	return 0;
}