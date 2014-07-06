#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int main()
{
	int n, r;
	int cover, count;
	int p[1024];
	scanf("%d %d", &r, &n);
	while(n != -1){
		for(int i=0; i<n; ++i){
			scanf("%d", p+i);
		}
		sort(p, p+n);
		cover = 0;
		count = 0;
		while(cover < n){
			int s = p[cover++];
			while(cover<n && s+r>=p[cover])
				cover++;
			s = p[cover-1];
			while(cover<n && s+r>=p[cover])
				cover++;
			++count;
		}
		printf("%d\n", count);
		scanf("%d %d", &r, &n);
	}
	return 0;
}