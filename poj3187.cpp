#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
	int n, s;
	int mat[11][11];
	int num[10];
	scanf("%d %d", &n, &s);
	memset(mat, 0, sizeof mat);
	mat[0][0] = 1;
	for(int i=0; i<n; ++i){
		for(int j=0; j<=i; ++j){
			mat[i+1][j] += mat[i][j];
			mat[i+1][j+1] += mat[i][j];
		}
	}
	for(int i=0; i<n; ++i)
		num[i] = i+1;
	do{
		int sum = 0;
		for(int i=0; i<n; ++i){
			sum += mat[n-1][i] * num[i];
		}
		if(sum == s){
			for(int i=0; i<n-1; ++i)
				printf("%d ", num[i]);
			printf("%d\n", num[n-1]);
			break;
		}
	}while(next_permutation(num, num+n));
	return 0;
}