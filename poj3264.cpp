#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>
using namespace std;

const int maxn = 50010;
const int inf = 999999999;

int data[1<<20], datb[1<<20];
int a[maxn];

int min(int a, int b)
{
	return a < b? a : b;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

void build(int k, int l, int r)
{
	if(l+1 == r)
		data[k] = datb[k] = a[l];
	else{
		build(k*2+1, l, (l+r)/2);
		build(k*2+2, (l+r)/2, r);
		data[k] = max(data[k*2+1], data[k*2+2]);
		datb[k] = min(datb[k*2+1], datb[k*2+2]);
	}
}

pair<int,int> query(int a, int b, int k, int l, int r)
{
	if(a<=l && r<=b)
		return make_pair(data[k], datb[k]);
	else if(l<b && a<r){
		pair<int,int> ra = query(a, b, k*2+1, l, (l+r)/2);
		pair<int,int> rb = query(a, b, k*2+2, (l+r)/2, r);
		pair<int,int> ret;
		ret.first = max(ra.first, rb.first);
		ret.second = min(ra.second, rb.second);
		return ret;
	}else
		return make_pair(0, inf);
}

int main()
{
	int n, q;
	int l, r;
	while(EOF != scanf("%d %d", &n, &q)){
		for(int i=0; i<n; ++i)
			scanf("%d", &a[i]);
		build(0, 0, n);
		for(int i=0; i<q; ++i){
			scanf("%d %d", &l, &r);
			pair<int,int> p = query(l-1, r, 0, 0, n);
			//printf("max:%d,min:%d\n", p.first, p.second);
			printf("%d\n", p.first-p.second);
		}
	}
	return 0;
}