#include <cstdio>
#include <cmath>

const int maxn = 1024;
double a[maxn][3];
double b[maxn];
double x[maxn];
int n;
double pa;

void solve()
{
	x[0] = b[0];
	x[n-1] = b[n-1];
	for(int i=1; i<n-1; ++i){
		double p = -a[i][0] / a[i-1][1];
		a[i][0] += p * a[i-1][1];
		a[i][1] += p * a[i-1][2];
		b[i] += p * b[i-1];
	}
	for(int i=n-2; i>0; --i)
		x[i] = (b[i] - a[i][2]*x[i+1]) / a[i][1];
}

bool satisfy(double d)
{
	for(int i=1; i<n-1; ++i){
		a[i][0] = 1;
		a[i][1] = -2;
		a[i][2] = 1;
		b[i] = 2;
	}
	a[0][1] = 1;
	a[n-1][1] = 1;
	b[0] = pa;
	b[n-1] = d;
	solve();
	for(int i=0; i<n; ++i)
		if(x[i] < 0)
			return false;
	return true;
}

int main()
{
	double ub, lb, mid;
	while(EOF != scanf("%d %lf", &n, &pa)){
		lb = 0.0;
		ub = 1e10;
		for(int i=0; i<100; ++i){
			mid = (lb+ub) / 2;
			if(satisfy(mid))
				ub = mid;
			else
				lb = mid;
		}
		printf("%.2f\n", mid);
	}
	return 0;
}