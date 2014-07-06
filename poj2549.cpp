#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>
using namespace std;

typedef pair<int, pair<int,int> > P;
P v[1<<20];

int main()
{
	int n, m;
	int s[1024];
	bool flag;
	int ans;
	while(EOF != scanf("%d", &n)){
		if(n == 0) break;
		for(int i=0; i<n; ++i)
			scanf("%d", &s[i]);
		sort(s, s+n);
		m = 0;
		for(int i=0; i<n; ++i)
			for(int j=i+1; j<n; ++j)
				v[m++] = make_pair(s[i]+s[j], make_pair(i, j));
		sort(v, v+m);
		flag = false;
		for(int i=n-1; i>=0&&!flag; --i){
			for(int j=0; j<n&&!flag; ++j){
				if(i == j) continue;
				int x = upper_bound(v, v+m, make_pair(s[i]-s[j], make_pair(-1, -1))) - v;
				int y = upper_bound(v, v+m, make_pair(s[i]-s[j], make_pair(n+1, n+1))) - v;
				while(x < y){
					if(i != v[x].second.first && i != v[x].second.second
						&& j != v[x].second.first && j != v[x].second.second){
							ans = s[i];
							flag = true;
							//printf("%d %d %d %d", s[v[x].second.first], s[v[x].second.second], s[j], s[i]);
							break;
					}
					++x;
				}
			}
		}
		if(flag){
			printf("%d\n", ans);
		}else{
			printf("no solution\n");
		}
	}
	return 0;
}