#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;
const int maxn = 16;
ll dp[2][1<<maxn];

int main()
{
	int h, w;
	ll *crt, *nxt;
	while(EOF != scanf("%d %d", &h, &w)){
		if(h==0 && w==0) break;
		crt = dp[0];
		nxt = dp[1];
		crt[0] = 1;
		for(int i=0; i<h; ++i){
			for(int j=0; j<w; ++j){
				for(int used=0; used<1<<w; ++used){
					if(used>>j & 1)
						nxt[used] = crt[used & ~(1<<j)];
					else{
						nxt[used] = 0;
						if(j-1>=0 && !(used>>(j-1) & 1))
							nxt[used] += crt[used | 1<<(j-1)];
						if(i-1>=0)
							nxt[used] += crt[used | (1<<j)];
					}
				}
				swap(crt, nxt);
			}
		}
		printf("%lld\n", crt[0]);
	}
	return 0;
}