#include<cstdio>
#include<cstring>
#include<vector>
#include <algorithm>
using namespace std;

void compute_prefix(const int p[], int pi[], int m)
{
	pi[0] = -1;
	int k = -1;
	for(int i=1; i<m; ++i){
		while(k>=0 && p[k+1]!=p[i])
			k = pi[k];
		if(p[k+1] == p[i])
			++k;
		pi[i] = k;
	}
}


int pit[100];
void extended_compute_prefix(const int p[], int pi[], int m)
{
	compute_prefix(p, pit, m);
	for(int i=0; i<m; ++i){
		if(pit[i] == -1)
			pi[i] = -1;
		else if(p[pit[i]+1] == p[i+1])
			pi[i] = pi[pit[i]];
		else pi[i] = pit[i];
	}
}

int kmp_matcher(const int t[], int n, const int p[], int m)
{
	vector<int> ret;
	int *pi = new int[m];
	compute_prefix(p, pi, m);
	int q = -1;
	for(int i=0; i<n; ++i){
		while(q>=0 && p[q+1]!=t[i])
			q = pi[q];
		if(p[q+1] == t[i])
			++q;
		if(q == m-1){
			ret.push_back(i);
			q = -1;
		}
	}
	delete pi;
	return ret.size();
}

int main()
{
	int n;
	int t[400], p[400];
	int ans;
	while(EOF !=scanf("%d", &n)){
		for(int i=0; i<n; ++i){
			scanf("%d", t+i);
		}
		ans = 0;
		for(int l=1; l<=n; ++l){
			for(int i=0; i<i-l; ++i){
				for(int j=i; j<i+l; ++j){
					p[j-i] = t[j];
				}
				ans = max(ans, kmp_matcher(t, n, p, l));
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}