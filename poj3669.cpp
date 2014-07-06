#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

int dx[] = {0, 1, -1, 0, 0};
int dy[] = {0, 0, 0, 1, -1};
int grid[310][310];

struct pos{
	int x, y, t;
};

int main()
{
	int m, x, y, t;
	queue<pos> q;
	scanf("%d", &m);
	for(int i=0; i<m; ++i){
		scanf("%d %d %d", &x, &y, &t);
		for(int j=0; j<5; ++j){
			int nx = x + dx[j];
			int ny = y + dy[j];
			if(nx<0 || ny<0)
				continue;
			if(grid[nx][ny] == 0 || grid[nx][ny]>t){
				grid[nx][ny] = t+1;
			}
		}
	}
	pos p;
	p.x = 0;
	p.y = 0;
	p.t = 1;
	q.push(p);
	bool finish = false;
	if(grid[0][0] == 0){
		puts("0");
		finish = true;
	}
	while(!q.empty() && !finish){
		p = q.front();
		q.pop();
		pos np;
		np.t = p.t + 1;
		for(int i=1; i<5; ++i){
			np.x = p.x + dx[i];
			np.y = p.y + dy[i];
			if(np.x < 0 || np.y<0)
				continue;
			if(grid[np.x][np.y] == 0){
				printf("%d\n", np.t-1);
				finish = true;
				break;
			}else if(grid[np.x][np.y]>np.t){
				grid[np.x][np.y] = np.t;
				q.push(np);
			}
		}
	}
	if(!finish)
		puts("-1");
	return 0;
}