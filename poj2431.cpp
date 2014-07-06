#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;

int main()
{
	int n, x, y, l, p;
	int ans = 0;
	priority_queue<int> fuel;
	priority_queue<pair<int,int> > stop;
	scanf("%d", &n);
	for(int i=0; i<n; ++i){
		scanf("%d %d", &x, &y);
		stop.push(make_pair(x, y));
	}
	scanf("%d %d", &l, &p);
	stop.push(make_pair(l-p, -1));
	stop.push(make_pair(0, 0));
	while(l != 0){
		pair<int,int> t = stop.top();
		stop.pop();
		l = t.first;
		if(t.second == -1){
			if(!fuel.empty()){
				stop.push(make_pair(l-fuel.top(), -1));
				++ans;
				fuel.pop();
			}else{
				break;
			}
		}else if(t.second>0){
			fuel.push(t.second);
		}
	}
	if(l == 0){
		printf("%d\n", ans);
	}else{
		puts("-1");
	}
	return 0;
}