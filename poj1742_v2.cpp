#include<cstdio>
#include<cstring>

#define maxn 128

int a[maxn], c[maxn];
//int aa[maxn], bb[maxn];
int f[100010];

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	while(n!=0 && m!=0){
		for(int i=0; i<n; ++i)
			scanf("%d", a+i);
		for(int i=0; i<n; ++i)
			scanf("%d", c+i);
		memset(f, 0, sizeof f);
		f[0] = 1;
		int ans = 0;
		for(int i=0; i<n; ++i){
			if(c[i] == 1){
				for(int j=m; j>=a[i]; --j)
					f[j] |= f[j-a[i]];
			}else if(c[i]*a[i] >= m){
				for(int j=0; j<=m-a[i]; ++j)
					f[j+a[i]] |= f[j];
			}else{
				//int *ps = aa, *pe = aa-1;
				//int *qs = bb, *qe = bb-1;
				for(int j=0; j<a[i]; ++j){
					for(int d=j, k=0; d<=m; d+=a[i]){
						if(f[d] == 1)
							k = c[i];
						else if(k > 0){
							--k;
							f[d] = 1;
						}
					}
				}
			}
		}
		for(int i=1; i<=m; ++i)
			if(f[i] > 0)
				++ans;
		printf("%d\n", ans);
		scanf("%d %d", &n, &m);
	}
	return 0;
}