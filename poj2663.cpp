#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

int main()
{
	ll dp[2][8];
	int n;
	while(EOF != scanf("%d", &n)){
		if(n == -1) break;
		memset(dp, 0, sizeof dp);
		ll *crt = dp[0];
		ll *next = dp[1];
		crt[0] = 1;
		for(int i=0; i<n; ++i){
			for(int j=0; j<3; ++j){
				for(int s=0; s<1<<3; ++s){
					if(s & 1<<j){
						next[s] = crt[s&~(1<<j)];
					}else{
						next[s] = 0;
						if(j && !(s&1<<(j-1)))
							next[s] += crt[s|1<<(j-1)];
						if(i>0)
							next[s] += crt[s|1<<j];
					}
				}
				swap(crt, next);
			}
		}
		printf("%lld\n", crt[0]);
	}
}