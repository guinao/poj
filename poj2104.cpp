#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int maxn = 100010;
const int B = 1024;

int a[maxn];
int num[maxn];
vector<int> bucket[maxn/B+1];

int main()
{
	int n, m;
	int b;
	int l, r, k;
	while(EOF != scanf("%d %d", &n, &m)){
		b = B;
		for(int i=0; i<=n/b; ++i)
			bucket[i].clear();
		for(int i=0; i<n; ++i){
			scanf("%d", &a[i]);
			num[i] = a[i];
			bucket[i/b].push_back(a[i]);
		}

		sort(num, num+n);
		for(int i=0; i<=n/b; ++i)
			sort(bucket[i].begin(), bucket[i].end());

		for(int i=0; i<m; ++i){
			scanf("%d %d %d", &l, &r, &k);
			l--;
			int ub = n-1, lb = -1;
			while(ub > lb+1){
				int mid = (ub+lb) / 2;
				int x = num[mid], c = 0;
				int tl = l, tr = r;

				while(tl<tr && tl%b!=0) if(a[tl++]<=x) ++c;
				while(tl<tr && tr%b!=0) if(a[--tr]<=x) ++c;

				while(tl < tr){
					c += upper_bound(bucket[tl/b].begin(), bucket[tl/b].end(), x)
						- bucket[tl/b].begin();
					tl += b;
				}

				if(c >= k)
					ub = mid;
				else
					lb = mid;
			}
			printf("%d\n", num[ub]);
		}
	}
	return 0;
}