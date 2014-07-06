#include<cstdio>
#include<cstring>
#include<set>
#include<algorithm>
using namespace std;

set<int> s;
int mat[5][5];
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

void dfs(int x, int y, int d, int v)
{
	if(d == 5)
		s.insert(v);
	else{
		for(int i=0; i<4; ++i){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(0<=nx&&nx<5&&0<=ny&&ny<5){
				dfs(nx, ny, d+1, v*10+mat[nx][ny]);
			}
		}
	}
}

int main()
{
	for(int i=0; i<5; ++i){
		for(int j=0; j<5; ++j){
			scanf("%d", &mat[i][j]);
		}
	}
	for(int i=0; i<5; ++i){
		for(int j=0; j<5; ++j){
			dfs(i, j, 0, mat[i][j]);
		}
	}
	printf("%d\n", s.size());
	return 0;
}