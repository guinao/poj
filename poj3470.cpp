#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

const int maxn = 50010;
const int inf = 999999999;

typedef pair<int,int> P;

pair<P,P> walls[maxn];
P pos[maxn];
P hit[maxn];
int cnt[maxn];
int len[maxn*2];
int data[1<<20];

struct pp{
	int index;
	int type;
	int x;
	int y1, y2;
	bool operator < (const pp& p) const
	{
		return this->x < p.x;
	}
}pps[maxn*2];

int Abs(int x)
{
	return x >= 0 ? x : -x;
}

int min(int a, int b)
{
	return a < b ? a : b;
}

int max(int a, int b)
{
	return a>b? a : b;
}

void cover(int a, int b, int x, int k, int l, int r)
{
	if(a<=l && r<=b){
		data[k] = x;
	}else if(l<b && a<r){
		if(data[k] != -1){
			data[k*2+1] = data[k];
			data[k*2+2] = data[k];
		}
		cover(a, b, x, k*2+1, l, (l+r)/2);
		cover(a, b, x, k*2+2, (l+r)/2, r);
		if(data[k*2+1] == data[k*2+2])
			data[k] = data[k*2+1];
		else
			data[k] = -1;
	}
	//printf("cover %d %d %d %d %d\n", l ,r, len[l], len[r], data[k]);
}

int query(int x, int k, int l, int r)
{
	//printf("query %d %d %d\n", len[l], len[r], x);
	int ret = -1;
	if(l>=r || x<len[l] || x>=len[r]){
		ret = -1;
	}else if(data[k]>=0){
		ret = data[k];
	}else if(l+1 < r){
		int mid = (l+r)/2;
		if(x<len[mid])
			ret = query(x, k*2+1, l, mid);
		else
			ret = query(x, k*2+2, mid, r);
	}
	return ret;
}

int main()
{
	int n, m, c;
	int x1, y1, x2, y2;
	int w;
	while(EOF != scanf("%d %d", &n, &m)){
		fill(hit, hit+m, make_pair(inf, -1));
		for(int i=0; i<n; ++i){
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			walls[i].first.first = min(x1, x2);
			walls[i].first.second = min(y1, y2);
			walls[i].second.first = max(x1, x2);
			walls[i].second.second = max(y1, y2);
		}
		for(int i=0; i<m; ++i){
			scanf("%d %d", &x1, &y1);
			pos[i].first = x1;
			pos[i].second = y1;
		}

		// x-scan
		w = 0;
		for(int i=0; i<n; ++i){
			len[w++] = walls[i].first.second*2;
			len[w++] = walls[i].second.second*2 + 1;
		}
		sort(len, len+w);
		w = unique(len, len+w) - len - 1;

		c = 0;
		for(int i=0; i<n; ++i){
			pps[c].index = i;
			pps[c].type = 0;
			pps[c].x = walls[i].second.first;
			pps[c].y1 = lower_bound(len, len+w, walls[i].first.second*2) - len;
			pps[c].y2 = lower_bound(len, len+w, walls[i].second.second*2+1) - len;
			++c;
		}
		for(int i=0; i<m; ++i){
			pps[c].x = pos[i].first;
			pps[c].y1= pos[i].second * 2;
			pps[c].type = 1;
			pps[c].index = i;
			++c;
		}
		sort(pps, pps+c);

		memset(data, -1, sizeof data);
		for(int i=0; i<c; ++i){
			//printf("%d %d %d %d %d\n", pps[i].type, pps[i].index, pps[i].x, pps[i].y1, pps[i].y2);
			if(pps[i].type == 0)
				cover(pps[i].y1, pps[i].y2, pps[i].index, 0, 0, w);
			else{
				int k = query(pps[i].y1, 0, 0, w);
				if(k != -1){
					int d = Abs(pps[i].x - walls[k].second.first);
					if(hit[pps[i].index].second==-1 || hit[pps[i].index].first>d){
						hit[pps[i].index].first = d;
						hit[pps[i].index].second = k;
					}
				}
			}
		}

		c = 0;
		for(int i=0; i<n; ++i){
			pps[c].index = i;
			pps[c].type = 0;
			pps[c].x = walls[i].first.first;
			pps[c].y1 = lower_bound(len, len+w, walls[i].first.second*2) - len;
			pps[c].y2 = lower_bound(len, len+w, walls[i].second.second*2+1) - len;
			++c;
		}
		for(int i=0; i<m; ++i){
			pps[c].x = pos[i].first;
			pps[c].y1= pos[i].second * 2;
			pps[c].type = 1;
			pps[c].index = i;
			++c;
		}
		sort(pps, pps+c);

		memset(data, -1, sizeof data);
		for(int i=c-1; i>=0; --i){
			if(pps[i].type == 0)
				cover(pps[i].y1, pps[i].y2, pps[i].index, 0, 0, w);
			else{
				int k = query(pps[i].y1, 0, 0, w);
				if(k != -1){
					int d = Abs(pps[i].x - walls[k].first.first);
					if(hit[pps[i].index].second==-1 || hit[pps[i].index].first>d){
						hit[pps[i].index].first = d;
						hit[pps[i].index].second = k;
					}
				}
			}
		}

		// y-scan
		w = 0;
		for(int i=0; i<n; ++i){
			len[w++] = walls[i].first.first*2;
			len[w++] = walls[i].second.first*2 + 1;
		}
		sort(len, len+w);
		w = unique(len, len+w) - len - 1;

		c = 0;
		for(int i=0; i<n; ++i){
			pps[c].index = i;
			pps[c].type = 0;
			pps[c].x = walls[i].second.second;
			pps[c].y1 = lower_bound(len, len+w, walls[i].first.first*2) - len;
			pps[c].y2 = lower_bound(len, len+w, walls[i].second.first*2+1) - len;
			++c;
		}
		for(int i=0; i<m; ++i){
			pps[c].x = pos[i].second;
			pps[c].y1= pos[i].first * 2;
			pps[c].type = 1;
			pps[c].index = i;
			++c;
		}
		sort(pps, pps+c);

		memset(data, -1, sizeof data);
		for(int i=0; i<c; ++i){
			if(pps[i].type == 0)
				cover(pps[i].y1, pps[i].y2, pps[i].index, 0, 0, w);
			else{
				int k = query(pps[i].y1, 0, 0, w);
				if(k != -1){
					int d = Abs(pps[i].x - walls[k].second.second);
					if(hit[pps[i].index].second==-1 || hit[pps[i].index].first>d){
						hit[pps[i].index].first = d;
						hit[pps[i].index].second = k;
					}
				}
			}
		}

		c = 0;
		for(int i=0; i<n; ++i){
			pps[c].index = i;
			pps[c].type = 0;
			pps[c].x = walls[i].first.second;
			pps[c].y1 = lower_bound(len, len+w, walls[i].first.first*2) - len;
			pps[c].y2 = lower_bound(len, len+w, walls[i].second.first*2+1) - len;
			++c;
		}
		for(int i=0; i<m; ++i){
			pps[c].x = pos[i].second;
			pps[c].y1= pos[i].first * 2;
			pps[c].type = 1;
			pps[c].index = i;
			++c;
		}
		sort(pps, pps+c);

		memset(data, -1, sizeof data);
		for(int i=c-1; i>=0; --i){
			if(pps[i].type == 0)
				cover(pps[i].y1, pps[i].y2, pps[i].index, 0, 0, w);
			else{
				int k = query(pps[i].y1, 0, 0, w);
				if(k != -1){
					int d = Abs(pps[i].x - walls[k].first.second);
					if(hit[pps[i].index].second==-1 || hit[pps[i].index].first>d){
						hit[pps[i].index].first = d;
						hit[pps[i].index].second = k;
					}
				}
			}
		}

		// count
		memset(cnt, 0, sizeof cnt);
		for(int i=0; i<m; ++i){
			if(hit[i].second != -1)
				cnt[hit[i].second]++;
		}

		for(int i=0; i<n; ++i)
			printf("%d\n", cnt[i]);
	}
	return 0;
}
