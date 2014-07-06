#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

struct cow{
	int s, t;
};

bool cmp(const cow& c1, const cow& c2)
{
	if(c1.s == c2.s)
		return c1.t > c2.t;
	return c1.s < c2.s;
}

vector<cow> v;

int main()
{
	int n, t;
	int a, b;
	int cnt = 0;
	scanf("%d %d", &n, &t);
	v.resize(n);
	for(int i=0; i<n; ++i){
		scanf("%d %d", &a, &b);
		v[i].s = a;
		v[i].t = b;
	}
	sort(v.begin(), v.end(), cmp);
	a = b = 0;
	for(int i=0; i<(int)v.size(); ++i){
		if(v[i].s <= a){
			if(v[i].t > b)
				b = v[i].t;
		}
		else if(v[i].s > a+1){
			if(a != b){
				++cnt;
				a = b;
			}
			else
				break;

			if(v[i].s <= a){
				if(v[i].t > b)
					b = v[i].t;
			}
			else if(v[i].s == a+1){
				++cnt;
				a = v[i].t;
				b= v[i].t;
			}
			else
				break;
		}else{
			++cnt;
			if(v[i].t > b)
				b = v[i].t;
			a = b;
		}
	}
	if(a >= t)
		printf("%d\n", cnt);
	else if(b >= t)
		printf("%d\n", cnt+1);
	else
		puts("-1");
	return 0;
}