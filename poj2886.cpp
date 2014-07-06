#include <cstdio>
#include <cstring>

const int maxn = 500010;

char name[maxn][16];
int num[maxn];
int cnt[maxn];
int bit[maxn];
int n, k, m;

void add(int i)
{
	while(i <= n){
		bit[i] += 1;
		i += i & -i;
	}
}

int sum(int i)
{
	int s = 0;
	while(i > 0){
		s += bit[i];
		i -= i & -i;
	}
	return s;
}

int main()
{
//	freopen("out.txt", "w", stdout);
	while(EOF != scanf("%d %d", &n, &k)){
		memset(cnt, 0, sizeof cnt);
		for(int i=1; i<=n; ++i){
			for(int j=i; j<=n; j+=i)
				cnt[j]++;
		}
		m = 1;
		for(int i=2; i<=n; ++i){
			if(cnt[m] < cnt[i])
				m = i;
		}

		for(int i=1; i<=n; ++i){
			scanf("%s %d", name[i], &num[i]);
		}

		memset(bit, 0, sizeof bit);
		int high, low, mid;
		for(int i=1; i<m; ++i){
//			printf("%s\n", name[k]);
			add(k);
			if(num[k]>0){
				num[k] = num[k]%(n-i);
				if(num[k] == 0)
					num[k] = n - i;
				low = num[k]-1;
				high = n;
				while(low+1 < high){
					mid = (low+high) / 2;
					int nk = k+mid;
					int inc;
					if(nk > n)
						inc = sum(n) - sum(k) + sum(nk-n);
					else
						inc = sum(nk) - sum(k);
					if(inc+num[k] > mid)
						low = mid;
					else
						high = mid;
				}
				k = k + high;
				if(k > n)
					k -= n;
			}else{
				num[k] = num[k]%(n-i);
				if(num[k] == 0)
					num[k] = -(n-i);
				low = num[k]+1;
				high = -n;
				while(-low+1 < -high){
					mid = (low+high) / 2;
					int nk = k+mid;
					int inc;
					if(nk <= 0)
						inc = sum(k-1) + sum(n) - sum(nk+n-1);
					else
						inc = sum(k-1) - sum(nk-1);
					if(inc-num[k] > -mid)
						low = mid;
					else
						high = mid;
				}
				k = k + high;
				if(k <= 0)
					k += n;
			}
		}
		printf("%s %d\n", name[k], cnt[m]);
	}

	return 0;
}