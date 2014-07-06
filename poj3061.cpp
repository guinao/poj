#include <cstdio>

const int maxn = 100001;
int a[maxn];

int main()
{
	int t;
	int n, s;
	int ans;
	int sum;
	int l, r;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &n, &s);
		ans = n + 1;
		for(int i=0; i<n; ++i)
			scanf("%d", &a[i]);
		l = r = 0;
		sum = 0;
		while(1){
			while(r<n && sum<s){
				sum += a[r++];
			}
			if(sum < s)
				break;
			if(r-l < ans)
				ans = r - l;
			sum -= a[l++];
		}
		if(ans > n)
			puts("0");
		else
			printf("%d\n", ans);
	}
	return 0;
}