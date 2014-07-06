#include<cstdio>

typedef long long ll;
int main()
{
	int n, s;
	ll sum = 0;
	int cost = 9999, ci, yi;
	scanf("%d %d", &n, &s);
	for(int i=0; i<n; ++i){
		scanf("%d %d", &ci, &yi);
		if(ci < cost){
			cost = ci;
		}
		sum += cost * yi;
		cost += s;
	}
	printf("%lld\n", sum);
	return 0;
}