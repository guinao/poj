#include <cstdio>
#include <vector>
#include <utility>
using namespace std;

typedef long long ll;

int main()
{
	ll n;
	vector<pair<int, int> > v;
	while(EOF != scanf("%lld", &n)){
		v.clear();
		ll l = 1, u = 1;
		ll sum = 0;
		while(l * l <= n){
			while(sum < n){
				sum += u * u;
				++u;
			}
			if(sum == n)
				v.push_back(make_pair(l, u-1));
			sum -= l * l;
			++l;
		}
		printf("%d\n", v.size());
		for(int i=0; i<(int)v.size(); ++i){
			printf("%d", v[i].second-v[i].first+1);
			for(int j=v[i].first; j<=v[i].second; ++j)
				printf(" %d", j);
			printf("\n");
		}
	}
}