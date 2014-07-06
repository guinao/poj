#include <cstdio>

const int maxn = 100001;
const int inf = 1000000000;

int n, m;
int expense[maxn];

bool satisfy(int d)
{
	int cnt = 1;
	int sum = 0;
	for(int i=0; i<n; ++i){
		if(sum + expense[i] > d){
			cnt++;
			sum = expense[i];
		}
		else
			sum += expense[i];
	}
	return cnt <= m;
}

int main()
{
	int lb, ub;
	while(EOF != scanf("%d %d", &n, &m)){
		ub = 1;
		lb = 0;
		for(int i=0; i<n; ++i){
			scanf("%d", &expense[i]);
			ub += expense[i];
			if(lb < expense[i])
				lb = expense[i]-1;
		}
		while(ub - lb > 1){
			int mid = (ub+lb) / 2;
			if(satisfy(mid))
				ub = mid;
			else
				lb = mid;
		}
		printf("%d\n", ub);
	}
	return 0;
}