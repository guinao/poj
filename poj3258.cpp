#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 50001;
const int inf = 1000000000;

int l, m, n;
int len[maxn];

bool satisfy(int d)
{
	int cnt = 0;
	int prev = 0;
	int f, e;
	for(f=0; f<n; ++f){
		if(len[f] < d)
			++cnt;
		else
			break;
	}
	for(e=n-1; e>=f; --e){
		if(l-len[e] < d)
			cnt++;
		else
			break;
	}
	prev = len[f];
	for(int i=f+1; i<=e; ++i){
		if(len[i] - prev < d)
			cnt++;
		else
			prev = len[i];
	}
	return m >= cnt;
}

int main()
{
	int lb, ub;
	while(EOF != scanf("%d %d %d", &l, &n, &m)){
		for(int i=0; i<n; ++i)
			scanf("%d", &len[i]);
		sort(len, len+n);
		lb = 0;
		ub = l+1;
		while(ub - lb > 1){
			printf("%d %d\n", lb, ub);
			int mid = (ub+lb) / 2;
			if(satisfy(mid))
				lb = mid;
			else
				ub = mid;
		}
		printf("%d\n", lb);
	}
	return 0;
}