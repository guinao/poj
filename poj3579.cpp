#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 100001;
int a[maxn];
int n, m, ans;

bool satisfy(int d)
{
	int sum = 0;
	for(int i=0; i<n; ++i)
		sum += lower_bound(a, a+n, a[i]+d)-a-i-1;
	return sum < m;
}

int main()
{
	int lb, ub;
	while(EOF != scanf("%d", &n)){
		m = (n * (n-1) / 2 + 1) / 2;
		for(int i=0; i<n; ++i)
			scanf("%d", &a[i]);
		sort(a, a+n);
		ub = a[n-1]+1;
		lb = 0;
		while(ub - lb > 1){
			int mid = (ub+lb) / 2;
			if(satisfy(mid))
				lb = mid;
			else
				ub = mid;
		}
		printf("%d\n", lb);
	}
}