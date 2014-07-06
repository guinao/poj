#include <cstdio>
#include <cstring>

const int maxn = 16;

int grid[maxn][maxn];
int ans[maxn][maxn];
int temp[maxn][maxn];
int dx[4] = {0, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int main()
{
	int m, n;
	int cnt;
	bool flag;
	while(EOF != scanf("%d %d", &m, &n)){
		for(int i=0; i<m; ++i){
			for(int j=0; j<n; ++j){
				scanf("%d", &grid[i][j]);
			}
		}
		cnt = -1;
		for(int i=0; i<(1<<n); ++i){
			for(int j=0; j<n; ++j){
				temp[0][j] = (i>>j) & 1;
			}

			for(int j=0; j<m-1; ++j){
				for(int k=0; k<n; ++k){
					int s = grid[j][k];
					for(int ii=0; ii<4; ++ii){
						int x = j+dx[ii];
						int y = k+dy[ii];
						if(x>=0 && x<m && y>=0 && y<n)
							s += temp[x][y];
					}
					temp[j+1][k] = s % 2;
				}
			}

			flag = true;
			for(int j=0; j<n; ++j){
				int s = grid[m-1][j];
				for(int ii=0; ii<4; ++ii){
					int x = m-1 + dx[ii];
					int y = j + dy[ii];
					if(x>=0 && x<m && y>=0 && y<n)
						s += temp[x][y];
				}
				if(s % 2 == 1){
					flag = false;
					break;
				}
			}
			if(!flag)
				continue;

			int s = 0;
			for(int j=0; j<m; ++j){
				for(int k=0; k<n; ++k){
					s += temp[j][k];
				}
			}

			if(cnt==-1 || s < cnt){
				cnt = s;
				memcpy(ans, temp, sizeof ans);
			}
		}

		if(cnt == -1){
			puts("IMPOSSIBLE");
		}else{
			for(int i=0; i<m; ++i){
				printf("%d", ans[i][0]);
				for(int j=1; j<n; ++j)
					printf(" %d", ans[i][j]);
				printf("\n");
			}
		}
	}
	return 0;
}