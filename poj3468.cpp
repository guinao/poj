#include <cstdio>
#include <cstring>

typedef long long ll;
const int data_size = (1<<18);

ll data[data_size], datb[data_size];
int max(int a, int b)
{
	return a > b ? a : b;
}

int min(int a, int b)
{
	return a<b? a : b;
}

void add(int a, int b, int x, int k, int l, int r)
{
	if(a<=l && r<=b)
		data[k] += x;
	else if(l<b && a<r){
		datb[k] += x*(min(b,r)-max(a,l));
		add(a, b, x, k*2+1, l, (l+r)/2);
		add(a, b, x, k*2+2, (l+r)/2, r);
	}
}

ll sum(int a, int b, int k, int l, int r)
{
	ll ret = 0;
	if(a<=l && r<=b){
		ret += datb[k] + (r-l)*data[k];
	}else if(l<b && a<r){
		ret += data[k]*(min(b,r)-max(a,l));
		ret += sum(a, b, k*2+1, l, (l+r)/2);
		ret += sum(a, b, k*2+2, (l+r)/2, r);
	}
	return ret;
}

int main()
{
	int n, q;
	int a, b, x;
	char buf[4];
	while(EOF != scanf("%d %d", &n, &q)){
		memset(data, 0, sizeof data);
		memset(datb, 0, sizeof datb);
		for(int i=0; i<n; ++i){
			scanf("%d", &x);
			add(i, i+1, x, 0, 0, n);
		}
		for(int i=0; i<q; ++i){
			scanf("%s", buf);
			if(buf[0] == 'Q'){
				scanf("%d %d", &a, &b);
				printf("%lld\n", sum(a-1, b, 0, 0, n));
			}else{
				scanf("%d %d %d", &a, &b, &x);
				add(a-1, b, x, 0, 0, n);
			}
		}
	}
	return 0;
}