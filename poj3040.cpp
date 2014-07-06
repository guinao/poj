#include<cstdio>
#include<vector>
#include<utility>
#include<cassert>
#include<algorithm>
using namespace std;

int main()
{
	int n;
	int c, x, y, ans;
	vector<pair<int, int> > v;
	int need[24];
	bool over;
	scanf("%d %d", &n, &c);
	ans = 0;
	for(int i=0; i<n; ++i){
		scanf("%d %d", &x, &y);
		if(x >= c)
			ans += y;
		else
			v.push_back(make_pair(x,y));
	}
	sort(v.begin(), v.end());
	while(true){
		int rest = c;
		memset(need, 0, sizeof need);
		for(int i=(int)v.size()-1; i>=0; --i){
			if(v[i].second != 0){
				if(v[i].second >= rest / v[i].first){
					need[i] = rest / v[i].first;
					rest = rest % v[i].first;
				}else{
					rest = rest - v[i].first * v[i].second;
					need[i] = v[i].second;
				}
			}
		}
		for(int i=0; i<(int)v.size() && rest>0; ++i){
			if(v[i].second > need[i]){
				rest -= v[i].first;
				need[i] += 1;
				assert(rest < 0);
			}
		}
		if(rest > 0)
			break;
		int cnt = c;
		for(int i=0; i<(int)v.size(); ++i){
			if(need[i] == 0)
				continue;
			cnt = min(cnt, v[i].second / need[i]);
		}
		if(cnt == 0)
			break;
		for(int i=0; i<(int)v.size(); ++i){
			v[i].second -= need[i] * cnt;
		}
		ans += cnt;
	}
	printf("%d\n", ans);
	return 0;
}