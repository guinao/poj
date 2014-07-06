#include <cstdio>
#include <algorithm>
#include <utility>
using namespace std;

const int maxn = 100001;

struct _cow{
	int v;
	int w;
	double y;
	int index;
	bool operator < (const _cow &c) const
	{
		return this->y > c.y;
	}
}cow[maxn];

int main()
{
	int n, k;
	int vi, wi;
	double s1, s2, sv, sw;
	while(EOF != scanf("%d %d", &n, &k)){
		for(int i=0; i<n; ++i){
			scanf("%d %d", &vi, &wi);
			cow[i].v = vi;
			cow[i].w = wi;
			cow[i].index = i+1;
		}
		sv = 0.0;
		sw = 0.0;
		for(int i=0; i<k; ++i){
			sv += cow[i].v;
			sw += cow[i].w;
		}
		s2 = sv / sw;
		do{
			s1 = s2;
			for(int i=0; i<n; ++i)
				cow[i].y = cow[i].v - s1 * cow[i].w;
			partial_sort(cow, cow+k, cow+n);
			sv = 0.0;
			sw = 0.0;
			for(int i=0; i<k; ++i){
				sv += cow[i].v;
				sw += cow[i].w;
			}
			s2 = sv / sw;
		}while(s2 - s1 > 1e-7);
		for(int i=0; i<k-1; ++i)
			printf("%d ", cow[i].index);
		printf("%d\n", cow[k-1].index);
	}
	return 0;
}