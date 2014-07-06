//用离散化可以显著提高速度，见讨论版
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 100010;

int num[maxn];
int data[1<<20];

void build(int k, int l, int r)
{
	if(l+1 == r)
		data[k] = 1;
	else{
		int mid = (l+r) / 2;
		build(k*2+1, l, mid);
		build(k*2+2, mid, r);
		if(num[l] == num[r-1])
			data[k] = r - l;
		else{
			data[k] = data[k*2+1] > data[k*2+2] ? 
				data[k*2+1] : data[k*2+2];
			int t = upper_bound(num+l, num+r, num[mid])
				- lower_bound(num+l, num+r, num[mid]);
			if(t > data[k])
				data[k] = t;
		}
	}
//	printf("%d %d %d\n", l, r, data[k]);
}

int query(int a, int b, int k, int l, int r)
{
	int ret = 0;
	if(a<=l && r<=b){
		ret = data[k];
	}else if(l<b && a<r){
		int m = (l+r) / 2;
		int ra = query(a, b, k*2+1, l, m);
		int rb = query(a, b, k*2+2, m, r);
		ret = ra > rb? ra : rb;
		if(num[m-1] == num[m]){
			l = l > a ? l : a;
			r = r < b ? r : b;
			int t = upper_bound(num+l, num+r, num[m])
				- lower_bound(num+l, num+r, num[m]);
			if(t > ret) ret = t;
		}
	}
//	printf("%d %d %d\n", l, r, ret);
	return ret;
}

int main()
{
	int n, q;
	int x, y;
	while(EOF != scanf("%d", &n)){
		if(n == 0) break;
		scanf("%d", &q);
		for(int i=0; i<n; ++i)
			scanf("%d", &num[i]);
		build(0, 0, n);
		for(int i=0; i<q; ++i){
			scanf("%d %d", &x, &y);
			printf("%d\n", query(x-1, y, 0, 0, n));
		}
	}
	return 0;
}