#include<cstdio>
#include<cstring>

int grid[350][350];

int max(int a, int b)
{
	return a > b ? a : b;
}

int main()
{
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; ++i){
		for(int j=0; j<=i; ++j){
			scanf("%d", &grid[i][j]);
		}
	}
	for(int i=1; i<n; ++i){
		grid[i][0] += grid[i-1][0];
		grid[i][i] += grid[i-1][i-1];
		for(int j=1; j<i; ++j){
			grid[i][j] += max(grid[i-1][j-1], grid[i-1][j]);
		}
	}
	int ans = 0;
	for(int i=0; i<n; ++i){
		ans = max(ans, grid[n-1][i]);
	}
	printf("%d\n", ans);
	return 0;
}