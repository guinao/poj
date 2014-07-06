#include<cstdio>
#include<cmath>
#include<stack>
#include<vector>
#include<utility>
#include<algorithm>

using namespace std;

struct node{
	double first;
	int second;
	int index;
};

bool cmp(const node& n1, const node& n2)
{
	if(n1.first != n2.first)
		return n1.first < n2.first;
	else
		return n1.second < n2.second;
}

vector<node> v;
bool mark[1024];

int main()
{
	int n, d;
	int x, y;
	int ca = 0;
	bool pass;
	stack<node> s;
	scanf("%d %d", &n, &d);
	while(n!=0 || d!=0){
		pass = true;
		v.resize(n<<1);
		memset(mark, 0, sizeof mark);
		for(int i=0; i<n; ++i){
			scanf("%d %d", &x, &y);
			if(!pass) continue;
			if(d >= y){
				double r = sqrt((double)d*d - (double)y*y);
				v[2*i].first= x - r;
				v[2*i].second = 0;
				v[2*i].index = i;
				v[2*i+1].first = x+r;
				v[2*i+1].second = 1;
				v[2*i+1].index = i;
			}else{
				pass = false;
			}
		}
		if(!pass)
			printf("Case %d: -1\n", ++ca);
		else{
			sort(v.begin(), v.end(), cmp);
			int ans = 0;
			double ll = v[0].first -1;
			while(!s.empty())
				s.pop();
			for(int i=0; i<v.size(); ++i){
				if(mark[v[i].index])
					continue;
				if(v[i].second == 0)
					s.push(v[i]);
				else{
					if(s.top().first<=ll && ll<=v[i].first);
					else{
						ll = v[i].first;
						++ans;
					}
					while(!s.empty()){
						mark[s.top().index] = true;
						s.pop();
					}
				}
			}
			printf("Case %d: %d\n", ++ca, ans);
		}
		scanf("%d %d", &n, &d);
	}
	return 0;
}