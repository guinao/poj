#include <cstdio>
#include <cstring>

const int n = 20;

int main()
{
	int bowl[n];
	int ans[n];
	int cnt = n+1;
	for(int i=0; i<n; ++i){
		scanf("%d", &bowl[i]);
	}
	for(int i=0; i<(1<<n); ++i){
		for(int j=0; j<n; ++j){
			ans[j] = (i>>j) & 1;
		}

		bool flag = true;
		for(int j=0; j<n; ++j){
			int s = bowl[j];
			for(int k=-1; k<=1; ++k){
				int x = j+k;
				if(x>=0 && x<n)
					s += ans[x];
			}
			if(s % 2 == 1){
				flag = false;
				break;
			}
		}
		if(flag){
			int s = 0;
			for(int i=0; i<n; ++i)
				s += ans[i];
			if(s < cnt)
				cnt = s;
		}
	}
	printf("%d\n", cnt);

	return 0;
}