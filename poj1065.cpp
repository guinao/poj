#include<cstdio>
#include<cstring>
#include<utility>
#include<algorithm>
using namespace std;

const int inf = 999999999;

pair<int,int> ws[5000];
bool mark[5000];

int main()
{
	int T;
	int w, l;
	int n;
	scanf("%d", &T);
	for(int re=1; re<=T; ++re){
		scanf("%d", &n);
		for(int i=0; i<n; ++i){
			scanf("%d %d", &l, &w);
			ws[i].first = l;
			ws[i].second = w;
		}
		memset(mark, 0, sizeof mark);
		sort(ws, ws+n);
		int pre = -1;
		int ans = 0;
		for(int i=0; i<n; ++i){
			if(mark[i])
				continue;
			++ans;
			pre = ws[i].second;
			mark[i] = true;
			for(int j=i+1; j<n; ++j){
				if(mark[j])
					continue;
				if(ws[j].second >= pre){
					pre = ws[j].second;
					mark[j] = true;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}