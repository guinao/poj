#include <cstdio>
#include <cstring>
#include <utility>
#include <queue>
using namespace std;

struct cow{
	int a;
	int b;
	cow(int a, int b){
		this->a = a;
		this->b = b;
	}

	friend bool operator < (const cow &c1, const cow &c2){
		return c1.b < c2.b;
	}

	friend bool operator > (const cow &c1, const cow &c2){
		return c1.b > c2.b;
	}
};

bool cmp(const cow& c1, const cow& c2)
{
	return c1.a < c2.a;
}

int main()
{
	int c, l;
	int x, y;
	vector<cow> vc;
	vector<pair<int,int> > vl;
	priority_queue<cow, vector<cow>, greater<cow>> pq;
	while(EOF != scanf("%d %d", &c, &l)){
		vc.clear();
		vl.clear();
		for(int i=0; i<c; ++i){
			scanf("%d %d", &x, &y);
			vc.push_back(cow(x, y));
		}
		for(int i=0; i<l; ++i){
			scanf("%d %d", &x, &y);
			vl.push_back(make_pair(x, y));
		}

		sort(vl.begin(), vl.end());
		sort(vc.begin(), vc.end(), cmp);
		int index = 0;
		int ans = 0;
		while(!pq.empty()) pq.pop();
		for(int i=0; i<l; ++i){
			while(index<c && vc[index].a<=vl[i].first){
				pq.push(vc[index]);
				++index;
			}
			while(!pq.empty() && vl[i].second>0){
				cow c = pq.top();
				pq.pop();
				if(vl[i].first<=c.b){
					vl[i].second--;
					ans++;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}