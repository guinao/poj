#include <cstdio>
#include <set>
#include <map>
using namespace std;

const int maxn = 1000001;
int a[maxn];

int main()
{
	set<int> s;
	map<int, int> m;
	int p, n;
	int cnt, ans;
	int l, r;
	while(EOF != scanf("%d", &p)){
		s.clear();
		m.clear();
		for(int i=0; i<p; ++i){
			scanf("%d", &a[i]);
			s.insert(a[i]);
			m[a[i]] = 0;
		}
		n = s.size();
		cnt = 0;
		l = r = 0;
		ans = p;
		while(1){
			while(cnt<n && r<p){
				if(m[a[r]] == 0)
					++cnt;
				++m[a[r]];
				++r;
			}
			if(cnt < n) break;
			if(ans > r-l)
				ans = r-l;
			--m[a[l]];
			if(m[a[l]] == 0)
				--cnt;
			++l;
		}
		printf("%d\n", ans);
	}
	return 0;
}