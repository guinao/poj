#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

const int maxn = 100001;

struct _cow{
	int a, s;
	int l, r;
	bool operator<(const _cow& c) const
	{
		return this->a < c.a;
	}
}cow[maxn];

bool cmp(const _cow& c1, const _cow& c2)
{
	return c1.s < c2.s;
}

int main()
{
	int n, c, f;
	int si, ai;
	int cnt, ans;
	priority_queue<_cow> pq;
	while(EOF != scanf("%d %d %d", &n, &c, &f)){
		n /= 2;
		for(int i=0; i<c; ++i){
			scanf("%d %d", &si, &ai);
			cow[i].s = si;
			cow[i].a = ai;
		}
		sort(cow, cow+c, cmp);
		while(!pq.empty())
			pq.pop();
		cnt = 0;
		for(int i=0; i<n; ++i){
			pq.push(cow[i]);
			cnt += cow[i].a;
		}
		for(int i=n; i<c-n; ++i){
			cow[i].l = cnt;
			cnt += cow[i].a;
			pq.push(cow[i]);
			cnt -= pq.top().a;
			pq.pop();
		}
		while(!pq.empty())
			pq.pop();
		cnt = 0;
		for(int i=0; i<n; ++i){
			pq.push(cow[c-i-1]);
			cnt += cow[c-i-1].a;
		}
		for(int i=n; i<c-n; ++i){
			cow[c-i-1].r = cnt;
			cnt += cow[c-i-1].a;
			pq.push(cow[c-i-1]);
			cnt -= pq.top().a;
			pq.pop();
		}
		ans = -1;
		for(int i=c-n-1; i>=n; --i){
			if(cow[i].l+cow[i].r+cow[i].a <= f){
				ans = cow[i].s;
				break;
			}
		}
		printf("%d\n", ans);
	}
}