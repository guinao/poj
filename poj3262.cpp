#include<cstdio>
#include<cstring>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;

typedef long long ll;

bool cmp(pair<ll,ll> &p1, pair<ll,ll> &p2)
{
	return (p1.first*p2.second) > (p1.second*p2.first);
}

int main()
{
	int n;
	ll sum = 0, ans = 0;
	ll t, d;
	vector<pair<ll, ll> > v;
	scanf("%d", &n);
	v.resize(n);
	for(int i=0; i<n; ++i){
		scanf("%lld %lld", &t, &d);
		sum += d;
		v[i] = make_pair(d, 2*t);
	}
	sort(v.begin(), v.end(), cmp);
	for(int i=0; i<n; ++i){
		sum -= v[i].first;
		ans += sum * v[i].second;
	}
	printf("%lld\n", ans);
	return 0;
}