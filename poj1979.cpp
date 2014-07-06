#include <cstdio>
#include <cstring>

char grid[32][32];
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

int dfs(int x, int y)
{
	int ret = 1;
	grid[x][y] = '#';
	for(int i=0; i<4; ++i){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(grid[nx][ny] == '.'){
			ret += dfs(nx, ny);
		}
	}
	return ret;
}

int main()
{
	int w, h;
	scanf("%d %d", &w, &h);
	while(w && h){
		memset(grid, '#', sizeof grid);
		bool find = false;
		int x, y;
		for(int i=1; i<=h; ++i){
			scanf("%s", &grid[i][1]);
			if(!find){
				for(int j=1; j<=w; ++j){
					if(grid[i][j] == '@'){
						find = true;
						x = i, y = j;
						break;
					}
				}
			}
		}
		printf("%d\n", dfs(x, y));
		scanf("%d %d", &w, &h);
	}
	return 0;
}