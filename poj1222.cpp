#include <cstdio>
#include <cstring>

const int maxn = 8;
int n = 6, m = 5;
int grid[maxn][maxn];
int ans[maxn][maxn];
int dx[4] = {-1, 0, 0, 0};
int dy[4] = {0, -1, 1, 0};

bool solve()
{
	for(int i=0; i<m-1; ++i){
		for(int j=0; j<n; ++j){
			int s = grid[i][j];
			for(int k=0; k<4; ++k){
				int x = i + dx[k];
				int y = j + dy[k];
				if(x>=0 && x<m && y>=0 && y<n)
					s += ans[x][y];
			}
			ans[i+1][j] = s % 2;
		}
	}

	for(int j=0; j<n; ++j){
		int s = grid[m-1][j];
		for(int k=0; k<4; ++k){
			int x = m-1 + dx[k];
			int y = j + dy[k];
			if(x>=0 && x<m && y>=0 && y<n)
				s += ans[x][y];
		}
		if(s % 2 == 1)
			return false;
	}
	
	return true;
}

int main()
{
	int cs;
	scanf("%d", &cs);
	for(int re=1; re<=cs; ++re){
		for(int i=0; i<m; ++i){
			for(int j=0; j<n; ++j){
				scanf("%d", &grid[i][j]);
			}
		}

		for(int k=0; k<(1<<n); ++k){
			for(int i=0; i<n; ++i)
				ans[0][i] = (k>>i) & 1;

			if(solve())
				break;
		}
		printf("PUZZLE #%d\n", re);
		for(int i=0; i<m; ++i){
			printf("%d", ans[i][0]);
			for(int j=1; j<n; ++j)
				printf(" %d", ans[i][j]);
			printf("\n");
		}
	}
	return 0;
}