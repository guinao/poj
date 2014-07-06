#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

typedef long long ll;
const ll inf = 9223372036854775807;

pair<ll, int> v[2<<18];

ll Abs(ll a)
{
	return a > 0 ? a : -a;
}

int main()
{
	ll s[40];
	int n, n1, n2;
	int len;
	ll ans;
	int sum;
	while(EOF != scanf("%d", &n)){
		if(n == 0) break;
		for(int i=0; i<n; ++i)
			scanf("%lld", &s[i]);
		n1 = n / 2;
		n2 = n - n1;
		len = 1<<n1;
		for(int i=0; i<len; ++i){
			ll a = 0;
			int b = 0;
			for(int j=0; j<n1; ++j){
				if(i>>j & 1){
					a += s[j];
					++b;
				}
			}
			v[i] = make_pair(a, b);
		}

		sort(v, v+len);
		int m = 1;
		for(int i=1; i<len; ++i){
			if(v[m-1].first!=v[i].first || v[m-1].second==0){
				v[m++] = v[i];
			}
		}

		ans = inf;
		sum = n + 1;
		for(int i=0; i<1<<n2; ++i){
			ll a = 0;
			int b = 0;
			for(int j=0; j<n2; ++j){
				if(i>>j & 1){
					a += s[n1+j];
					++b;
				}
			}
			int k = upper_bound(v, v+m, make_pair(-a, 0)) - v;
			if(k < m && v[k].second+b>0){
				if(Abs(a + v[k].first) < ans){
					ans = Abs(a + v[k].first);
					sum = b + v[k].second;
				}else if(Abs(a + v[k].first)==ans && b+v[k].second<sum){
					sum = b + v[k].second;
				}
			}
			k = k - 1;
			if(k >= 0 && v[k].second+b>0){
				if(Abs(a + v[k].first) < ans){
					ans = Abs(a + v[k].first);
					sum = b + v[k].second;
				}else if(Abs(a + v[k].first)==ans && b+v[k].second<sum){
					sum = b + v[k].second;
				}
			}
			k = k - 1;
			if(k >= 0 && v[k].second+b>0){
				if(Abs(a + v[k].first) < ans){
					ans = Abs(a + v[k].first);
					sum = b + v[k].second;
				}else if(Abs(a + v[k].first)==ans && b+v[k].second<sum){
					sum = b + v[k].second;
				}
			}
		}

		printf("%lld %d\n", ans, sum);
	}
	return 0;
}