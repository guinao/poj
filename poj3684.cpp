#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int maxn = 128;
int N, H, R, T;

int main()
{
	int ca;
	double height[maxn];
	scanf("%d\n", &ca);
	for(int re=0; re<ca; ++re){
		scanf("%d %d %d %d", &N, &H, &R, &T);
		double tt = sqrt(2 * H / 10.);
		for(int i=0; i<N; ++i){
			int t = T - i;
			if(t <= 0){
				height[i] = H;
			}else{
				int k = t / tt;
				if(k % 2 == 0){
					height[i] = H - 0.5*10*(t-k*tt)*(t-k*tt);
				}else{
					height[i] = H - 0.5*10*(k*tt+tt-t)*(k*tt+tt-t);
				}
			}
		}
		sort(height, height+N);
		printf("%.2f", height[0]);
		for(int i=1; i<N; ++i){
			printf(" %.2f", height[i]+2*i*R/100.0);
		}
		printf("\n");
	}
	return 0;
}