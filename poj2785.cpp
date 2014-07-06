#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 5192;
int a[maxn];
int b[maxn];
int c[maxn];
int d[maxn];

int main()
{
	int n;
	vector<int> v1, v2;
	long long ans;
	while(EOF != scanf("%d", &n)){
		for(int i=0; i<n; ++i){
			scanf("%d %d %d %d", &a[i], &b[i], &c[i], &d[i]);
		}
		v1.resize(n * n);
		v2.resize(n * n);
		for(int i=0; i<n; ++i){
			for(int j=0; j<n; ++j){
				v1[i*n+j] = a[i] + b[j];
				v2[i*n+j] = c[i] + d[j];
			}
		}
		sort(v2.begin(), v2.end());
		ans = 0;
		for(int i=0; i<(int)v1.size(); ++i){
			ans += upper_bound(v2.begin(), v2.end(), -v1[i]) - lower_bound(v2.begin(), v2.end(), -v1[i]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}