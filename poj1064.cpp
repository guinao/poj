#include <cstdio>
#include <cmath>
#include <cstring>

double cable[10001];
int n ,k;

bool judge(double len)
{
	int cnt = 0;
	for(int i=0; i<n; ++i)
		cnt += (int)(cable[i]/len);
	return cnt >= k;
}

int main()
{
	double up, low, mid;
	while(EOF != scanf("%d %d", &n, &k)){
		up = 0.0;
		for(int i=0; i<n; ++i){
			scanf("%lf", &cable[i]);
			if(cable[i] > up)
				up = cable[i];
		}
		up *= 3;
		low = 0.0;
		for(int i=0; i<100; ++i){
			mid = (up+low) / 2;
			if(judge(mid))
				low = mid;
			else
				up = mid;
		}
		printf("%.2f\n", floor(mid*100)/100);
	}
	return 0;
}