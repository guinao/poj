#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1024;
int a[maxn];
int b[maxn];
double c[maxn];
int n, k;

bool satisfy(double d)
{
	double sum = 0.0;
	for(int i=0; i<n; ++i){
		c[i] = a[i] - b[i] * d;
		sum += c[i];
	}
	sort(c, c+n);
	for(int i=0; i<k; ++i)
		sum -= c[i];
	return sum >= 0;
}

int main()
{
	double lb, ub, mid;
	while(EOF != scanf("%d %d", &n,&k)){
		if(n==0 && k==0) break;
		for(int i=0; i<n; ++i)
			scanf("%d", &a[i]);
		for(int i=0; i<n; ++i)
			scanf("%d", &b[i]);
		lb = 0.0;
		ub = 1.0;
		for(int i=0; i<100; ++i){
			mid = (lb+ub) / 2;
			if(satisfy(mid))
				lb = mid;
			else
				ub = mid;
		}
		printf("%d\n", (int)(mid*100+0.5));
	}
	return 0;
}