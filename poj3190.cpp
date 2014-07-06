#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

struct cow{
	int a, b, i;
};

bool cmp(const cow& c1, const cow& c2)
{
	if(c1.a != c2.a)
		return c1.a < c2.a;
	return
		c1.b < c2.b;
}

int stall[50001];

int main()
{
	int n;
	int a, b;
	vector<cow> v;
	priority_queue<int> q;
	scanf("%d", &n);
	v.resize(n*2);
	for(int i=0; i<n; ++i){
		scanf("%d %d", &a, &b);
		v[i*2].a = a;
		v[i*2].b = 0;
		v[i*2].i = i;
		v[i*2+1].a = b;
		v[i*2+1].b = 1;
		v[i*2+1].i = i;
	}
	sort(v.begin(), v.end(), cmp);
	int ans = 0;
	for(int i=0; i<v.size(); ++i){
		if(v[i].b == 0){
			if(!q.empty()){
				stall[v[i].i] = q.top();
				q.pop();
			}else{
				stall[v[i].i] = ++ans;
			}
		}
		else{
			q.push(stall[v[i].i]);
		}
	}
	printf("%d\n", ans);
	for(int i=0; i<n; ++i)
		printf("%d\n", stall[i]);
	return 0;
}