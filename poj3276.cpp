#include <cstdio>
#include <cstring>

const int maxn = 5002;
char dir[maxn];
int f[maxn];

int main()
{
	int n, k;
	int ans;
	bool flag;
	while(EOF != scanf("%d", &n)){
		for(int i=0; i<n; ++i)
			scanf("%s", dir+i);
		flag = true;
		for(int i=0; i<n; ++i){
			if(dir[i] == 'B'){
				flag = false;
				break;
			}
		}
		if(flag){
			puts("0 0");
			continue;
		}
		ans = maxn+1;
		f[0] = 0;
		for(int i=1; i<=n; ++i){
			int cnt = 0;
			for(int j=0; j<=n-i; ++j){
				int a = dir[j] == 'F' ? 0 : 1;
				a += f[j];
				if(j-i+1 >= 0)
					a -= f[j-i+1];
				if(a % 2 == 1){
					f[j+1] = f[j] + 1;
					++cnt;
				}
				else{
					f[j+1] = f[j];
				}
			}
			flag = true;
			for(int j=n-i+1; j<n; ++j){
				int a = dir[j]=='F' ? 0 : 1;
				if((f[n-i+1]-f[j-i+1]+a) % 2 == 1){
					flag = false;
					break;
				}
			}
			if(flag && cnt < ans){
				ans = cnt;
				k = i;
			}
		}
		printf("%d %d\n", k, ans);
	}
	return 0;
}