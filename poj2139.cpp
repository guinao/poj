#include <cstdio>
#include <cstring>

const int maxn = 320;
const int inf = 999999999;

int d[320][320];

void warshall_floyd(int n){
	for(int k=1; k<=n; ++k)
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=n; ++j)
				if(d[i][j] > d[i][k]+d[k][j])
					d[i][j] = d[i][k]+d[k][j];
}

int main()
{
	int n, m;
	int x, y[300];
	while(EOF != scanf("%d %d", &n, &m)){
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=n; ++j){
				d[i][j] = inf;
			}
			d[i][i] = 0;
		}
		for(int i=0; i<m; ++i){
			scanf("%d", &x);
			for(int j=0; j<x; ++j)
				scanf("%d", &y[j]);

			for(int j=0; j<x; ++j)
				for(int k=j+1; k<x; ++k)
					d[y[j]][y[k]] = d[y[k]][y[j]] = 1;
		}
		warshall_floyd(n);
		int ans = inf;
		int sum;
		for(int i=1; i<=n; ++i){
			sum = 0;
			for(int j=1; j<=n; ++j){
				sum += d[i][j];
			}
			if(sum < ans)
				ans = sum;
		}
		printf("%d\n", ans*100/(n-1));
	}
	return 0;
}