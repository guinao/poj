//Ì°ĞÄ¼ÓÏß¶ÎÊ÷
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 50010;
const int inf = 999999999;

int data[1<<20];
struct region{
	int a, b, c;
	bool operator<(const region& r)
	{
		if(this->b != r.b)
			return this->b < r.b;
		else
			return this->a < r.a;
	}
}r[maxn];

int max(int a, int b)
{
	return a > b ? a : b;
}

int min(int a, int b)
{
	return a < b ? a : b;
}

int add(int a, int b, int c, int k, int l, int r)
{
	if(c <= 0)
		return 0;
	int ret = c;
	if(a<=l && r<=b){
		if(c+data[k] >= r-l){
			ret = c + data[k] - r + l;
			data[k] = r - l;
		}else{
			ret = add(a, b, c, k*2+2, (l+r)/2, r);
			ret = add(a, b, ret, k*2+1, l, (l+r)/2);
			data[k] = data[k*2+1] + data[2*k+2];
		}
	}else if(l<b && a<r){
		if(data[k] == r-l){
			ret = c;
		}else{
			ret = add(a, b, c, k*2+2, (l+r)/2, r);
			ret = add(a, b, ret, k*2+1, l, (l+r)/2);
			data[k] = data[k*2+1] + data[k*2+2];
		}
	}
	return ret;
}

int query(int a, int b, int k, int l, int r)
{
	int ret = 0;
	if(a<=l && r<=b){
		ret = data[k];
	}else if(l<b && a<r){
		if(data[k] == r-l){
			ret = min(r,b) - max(l, a);
		}else{
			ret = query(a, b, k*2+1, l, (l+r)/2);
			ret += query(a, b, k*2+2, (l+r)/2, r);
		}
	}
	return ret;
}

int main()
{
	int n;
	int a, b, c;
	int s, t;
	while(EOF != scanf("%d", &n)){
		s = inf;
		t = 0;
		for(int i=0; i<n; ++i){
			scanf("%d %d %d", &a, &b, &c);
			r[i].a = a;
			r[i].b = b+1;
			r[i].c = c;
			s = min(s, a);
			t = max(t, b+1);
		}
		sort(r, r+n);
		memset(data, 0, sizeof data);

		for(int i=0; i<n; ++i){
			c = r[i].c - query(r[i].a, r[i].b, 0, s, t);
			add(r[i].a, r[i].b, c, 0, s, t);
//			printf("%d %d %d %d\n", r[i].a, r[i].b, r[i].c, data[0]);
		}

		printf("%d\n", data[0]);
	}
	return 0;
}