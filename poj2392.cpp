#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int dp[40010];

struct _block{
	int a;
	int c;
	int h;
}block[400];

bool cmp(const _block &b1, const _block &b2)
{
	return b1.a < b2.a;
}

int main()
{
	int k;
	int x, y, z;
	int m;
	while(EOF != scanf("%d", &k)){
		m = 0;
		for(int i=0; i<k; ++i){
			scanf("%d %d %d", &x, &y, &z);
			block[i].h = x;
			block[i].a = y;
			block[i].c = z;
			m = max(m, y);
		}
		sort(block, block+k, cmp);
		memset(dp, 0, sizeof dp);
		dp[0] = 1;
		for(int i=0; i<k; ++i){
			for(int j=0; j<block[i].c; ++j){
				for(int p=block[i].a; p>=block[i].h; --p){
					dp[p] |= dp[p-block[i].h];
				}
			}
		}
		for(int i=m; i>=0; --i){
			if(dp[i] != 0){
				printf("%d\n", i);
				break;
			}
		}
	}
}