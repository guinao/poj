#include <cstdio>

const int maxn = 100001;
const int inf = 1000000000;

int n, k;
int a[maxn];

bool satisfy(int d)
{
	int sum = 0;
	for(int i=0; i<n; ++i)
		if(a[i] > d)
			sum += (a[i]-d+k-2) / (k-1);
	return sum <= d;
}

int main()
{
	int ub, lb;
	while(EOF != scanf("%d", &n)){
		ub = lb = 0;
		for(int i=0; i<n; ++i){
			scanf("%d", &a[i]);
			if(a[i] > ub)
				ub = a[i];
		}
		scanf("%d", &k);
		if(k > 1){
			while(ub - lb > 1){
				int mid = (lb + ub) / 2;
				if(satisfy(mid))
					ub = mid;
				else
					lb = mid;
			}
		}
		printf("%d\n", ub);
	}
	return 0;
}