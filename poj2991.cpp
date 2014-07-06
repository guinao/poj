#include <cstdio>
#include <cmath>
#include <cstring>

const int maxn = 10010;
const int st_size = (1<<15) - 1;
const double pi = acos(-1.0);

int len[maxn];
double prev[maxn];
double vx[st_size], vy[st_size];
double ang[st_size];

void init(int k, int l, int r)
{
	ang[k] = vx[k] = 0.0;
	
	if(l+1 == r){
		vy[k] = len[l];
	}else{
		int chl = k * 2 + 1;
		int chr = k * 2 + 2;
		int m = (l + r) / 2;
		init(chl, l, m);
		init(chr, m, r);
		vy[k] = vy[chl] + vy[chr];
	}
}

void update(int s, double a, int k, int l, int r)
{
	if(l+1<r && l<=s && s<r){
		int chl = k * 2 + 1;
		int chr = k * 2 + 2;
		int m = (l + r) / 2;
		update(s, a, chl, l, m);
		update(s, a, chr, m, r);
		if(s < m)
			ang[k] += a;
		double s = sin(ang[k]), c = cos(ang[k]);
		vx[k] = vx[chl] + (c*vx[chr] - s*vy[chr]);
		vy[k] = vy[chl] + (s*vx[chr] + c*vy[chr]);
	}
}

int main()
{
	int n, c, s, a;
	while(EOF != scanf("%d %d", &n, &c)){
		for(int i=0; i<n; ++i){
			scanf("%d", &len[i]);
			prev[i] = pi;
		}
		init(0, 0, n);
		for(int i=0; i<c; ++i){
			scanf("%d %d", &s , &a);
			double ra = a / 360. * 2 * pi;
			update(s-1, ra-prev[s-1], 0, 0, n);
			prev[s-1] = ra;
			printf("%.2lf %.2lf\n", vx[0], vy[0]);
		}
	}
	return 0;
}