#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

const int maxn = 100001;
vector<pair<int,int> > p;
int bit[maxn];
int w, h;

struct line{
	int type;
	int x;
	int y;
}l[maxn*2];

bool cmp(const line& l1, const line& l2)
{
	if(l1.x != l2.x)
		return l1.x < l2.x;
	else if(l1.y != l2.y)
		return l1.y < l2.y;
	else
		return l1.type < l2.type;
}

bool cmp2(const pair<int,int>& p1, const pair<int,int>& p2)
{
	if(p1.second != p2.second)
		return p1.second < p2.second;
	return p1.first < p2.first;
}

void add(int i, int x)
{
	while(i <= h){
		bit[i] += x;
		i += i & -i;
	}
}

int sum(int i)
{
	int s = 0;
	while(i > 0){
		s += bit[i];
		i -= i & -i;
	}
	return s;
}

int main()
{
	int n, m;
	int x, y;
	int ans;
	vector<int> v;
	while(EOF != scanf("%d", &n)){
		p.resize(n);
		v.resize(n);
		for(int i=0; i<n; ++i){
			scanf("%d %d", &x, &y);
			p[i].first = x;
			p[i].second = y;
			v[i] = y;
		}

		sort(v.begin(), v.end());
		v.erase(unique(v.begin(), v.end()), v.end());
		for(int i=0; i<n; ++i){
			p[i].second = lower_bound(v.begin(), v.end(), p[i].second) - v.begin() + 1;
		}
		h = v.size();

		m = 0;
		sort(p.begin(), p.end(), cmp2);
		for(int i=0; i<n; ++i){
			bool flag = false;
			if(i-1>=0 && p[i-1].second==p[i].second){
				l[m].x = p[i].first;
				l[m].type = 2;
				l[m].y = p[i].second;
				++m;
				flag = true;
			}
			if(i+1<n && p[i+1].second==p[i].second){
				l[m].x = p[i].first;
				l[m].type = 0;
				l[m].y = p[i].second;
				++m;
				flag = true;
			}
			if(!flag){
				l[m].x = p[i].first;
				l[m].type = 1;
				l[m].y = p[i].second;
				++m;
			}
		}
		sort(l, l+m, cmp);

		ans = n;
		for(int i=0; i<m; ++i){
			if(i-1>=0 && l[i-1].x == l[i].x && l[i-1].y != l[i].y){
				ans += sum(l[i].y-1) - sum(l[i-1].y);
			}
			if(l[i].type==0){
				add(l[i].y, 1);
			}else if(l[i].type == 2){
				add(l[i].y, -1);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}