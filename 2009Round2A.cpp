#include<cstdio>
#include<cstring>

int rows[64];

void change(int a, int b)
{
	int x = rows[b];
	for(int i=b; i>a; --i)
		rows[i] = rows[i-1];
	rows[a] = x;
}

int main()
{
	freopen("A-large-practice.in", "r", stdin);
	freopen("large.out", "w", stdout);
	int n, t, ans;
	char buf[64];
	scanf("%d", &t);
	for(int re=1; re<=t; ++re){
		scanf("%d", &n);
		for(int i=0; i<n; ++i){
			int cnt = 0;
			scanf("%s",buf);
			for(int j=0; j<n; ++j){
				if(buf[j] == '1')
					cnt = j;
			}
			rows[i] = cnt;
		}
		ans = 0;
		for(int i=0; i<n; ++i)if(rows[i]>i){
			for(int j=i+1; j<n; ++j){
				if(rows[j] <= i){
					change(i, j);
					ans += j-i;
					break;
				}
			}
		}
		printf("Case #%d: %d\n", re, ans);
	}
	return 0;
}