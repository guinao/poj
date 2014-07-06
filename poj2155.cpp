#include <cstdio>
#include <cstring>

const int maxn = 1024;

int bit[maxn][maxn];
int n;

void add(int x, int y)
{
	for(int i=x; i>0; i-=i&-i){
		for(int j=y; j>0; j-=j&-j){
			bit[i][j] = (bit[i][j]+1) % 2;
		}
	}
}

int sum(int x, int y)
{
	int s = 0;
	for(int i=x; i<=n; i+=i&-i){
		for(int j=y; j<=n; j+=j&-j){
			s = (s + bit[i][j]) % 2;
		}
	}
	return s;
};

int main()
{
	int r;
	int t;
	int x1, y1, x2, y2;
	char buf[4];
	scanf("%d", &r);
	for(int re=0; re<r; ++re){
		if(re > 0)
			printf("\n");
		memset(bit, 0, sizeof bit);
		scanf("%d %d", &n, &t);
		for(int i=0; i<t; ++i){
			scanf("%s", buf);
			if(buf[0] == 'Q'){
				scanf("%d %d", &x1, &y1);
				printf("%d\n", sum(x1, y1));
			}else{
				scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
				add(x2, y2);
				add(x2, y1-1);
				add(x1-1, y2);
				add(x1-1, y1-1);
			}
		}
	}
	return 0;
}