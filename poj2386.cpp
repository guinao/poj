#include<cstdio>
#include<cstring>

const int maxn = 128;

int visit[maxn][maxn];
char grid[maxn][maxn];
int n, m;

void dfs(int x, int y)
{
	visit[x][y] = 1;
	for(int dx=-1; dx<=1; ++dx){
		for(int dy=-1; dy<=1; ++dy){
			int nx = x+dx, ny = y+dy;
			if(0<=nx&&nx<n && 0<=ny&&ny<m){
				if(grid[nx][ny]=='W' && visit[nx][ny]==0)
					dfs(nx, ny);
			}
		}
	}
	return ;
}

int main()
{
	int ans;
	scanf("%d %d", &n, &m);
	for(int i=0; i<n; ++i){
		scanf("%s", grid[i]);
	}
	ans = 0;
	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
			if(grid[i][j]=='W' && visit[i][j]==0){
				dfs(i, j);
				++ans;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}