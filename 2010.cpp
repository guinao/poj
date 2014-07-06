#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long ll;

struct _cow{
	ll score;
	ll aid;
	int lval;
	int rval;

	bool operator <(const _cow & c) const
	{
		return this->aid < c.aid;
	}

	bool operator >(const _cow &c) const
	{
		return this->aid > c.aid;
	}

}v[100001];

bool cmp(const _cow& c1, const _cow& c2)
{
	return c1.score > c2.score;
}

void foo(char **p)
{
	printf("%s", p+2);
}

int main()
{
	int n, c, f;
	ll x, y;
	ll cost;
//	vector<_cow> v;
	priority_queue<_cow, vector<_cow>, less<_cow> > pql;
	while(EOF != scanf("%d %d %d", &n, &c, &f)){
		for(int i=0; i<c; ++i){
			scanf("%lld %lld", &x, &y);
			v[i].score = x;
			v[i].aid = y;
		}
		sort(v, v+c, cmp);
		if(n == 1){
			int ans = -1;
			for(int i=0; i<c; ++i){
				if(v[i].aid <= f){
					ans = v[i].score;
					break;
				}
			}
			printf("%d\n", ans);
		}
		else{
			cost = 0;
			while(!pql.empty())
				pql.pop();
			for(int i=0; i<n/2; ++i){
				pql.push(v[i]);
				cost += v[i].aid;
			}
			for(int i=n/2; i+n/2<c; ++i){
				v[i].lval = cost + v[i].aid;
				if(pql.top().aid > v[i].aid){
					cost = cost - pql.top().aid + v[i].aid;
					pql.pop();
					pql.push(v[i]);
				}
			}
			while(!pql.empty())
				pql.pop();
			cost = 0;
			for(int i=1; i<=n/2; ++i){
				pql.push(v[c-i]);
				cost += v[c-i].aid;
			}
			for(int i=n/2+1; i+n/2<=c; ++i){
				v[c-i].rval = cost;
				if(v[c-i].aid < pql.top().aid){
					cost = cost - pql.top().aid + v[c-i].aid;
					pql.pop();
					pql.push(v[c-i]);
				}
			}
			int ans = -1;
			for(int i=n/2; i+n/2<c; ++i){
				if(v[i].lval+v[i].rval <= f){
					ans = v[i].score;
					break;
				}
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}