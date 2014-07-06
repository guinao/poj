#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>
using namespace std;

const int inf = 2000000000;
pair<int,int> data[100010];

int main()
{
	int n, k, t;
	int l, u;
	int ansl, ansu;
	int x, y, z;
	while(EOF != scanf("%d %d", &n, &k)){
		if(n == 0 && k == 0)
			break;
		data[0] = make_pair(0, 0);
		for(int i=1; i<=n; ++i){
			scanf("%d", &x);
			data[i].first = data[i-1].first + x;
			data[i].second = i;
		}
		sort(data, data+n+1);
		for(int i=0; i<k; ++i){
			scanf("%d", &t);
			ansl = 1;
			ansu = n;
			l = u = 0;
			y = inf;
			x = -1;
			z = 0;
			while(u<n && x!=t){
				while(u<n && (z<t || l==u)){
					u++;
					z = data[u].first - data[l].first;
					if(abs(z-t) < y){
						ansl = min(data[l].second, data[u].second);
						ansu = max(data[l].second, data[u].second);
						x = z;
						y = abs(z-t);
					}
				}
				while(l < u && z > t){
					l++;
					if(u == l)
						break;
					z = data[u].first - data[l].first;
					if(abs(z-t) < y){
						ansl = min(data[l].second, data[u].second);
						ansu = max(data[l].second, data[u].second);
						x = z;
						y = abs(z-t);
					}
				}
			}
			printf("%d %d %d\n", x, ansl+1, ansu);
		}
	}
	return 0;
}