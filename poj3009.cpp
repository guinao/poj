#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int board[32][32];
int w, h;

bool inbound(int x, int y)
{
	return 0<=x&&x<h&&0<=y&&y<w;
}

int dfs(int x, int y, int d)
{
	int ret = -1;
	for(int i=0; i<4; ++i){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(inbound(nx, ny) && board[nx][ny]!=1){
			while(inbound(nx, ny)){
				if(board[nx][ny] == 0){
					nx += dx[i];
					ny += dy[i];
				}else if(board[nx][ny] == 1){
					if(d+1 <= 10){
						board[nx][ny] = 0;
						int v = dfs(nx-dx[i], ny-dy[i], d+1);
						if(v!=-1&&(ret==-1||ret>v)){
							ret = v;
						}
						board[nx][ny] = 1;
					}
					break;
				}else if(board[nx][ny] == 3){
					return d;
				}
			}
		}
	}
	return ret;
}

int main()
{
	scanf("%d %d", &w, &h);
	int sx, sy;
	while(w!=0 && h!=0){
		for(int i=0; i<h; ++i){
			for(int j=0; j<w; ++j){
				scanf("%d", &board[i][j]);
				if(board[i][j] == 2){
					sx = i;
					sy = j;
					board[i][j] = 0;
				}
			}
		}
		printf("%d\n", dfs(sx, sy, 1));
		scanf("%d %d", &w, &h);
	}
	return 0;
}