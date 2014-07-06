#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int fh(int n)
{
	return (n<<2) | 1;
}

bool prime[250002];

int main()
{
	vector<int> p;
	p.clear();
	for(int i=1; i<250002; ++i){
		if(!prime[i]){
			int a = fh(i);
			p.push_back(a);
			int j = 1;
			int z = fh(j);
			while(z*a+1 <= 1000001){
				prime[z*a/4] = true;
				++j;
				z = fh(j);
			}
		}
	}

	vector<int> semip;
	semip.clear();
	for(int i=0; i<p.size(); ++i){
		for(int j=0;j<=i; ++j){
			int next = p[i]*p[j];
			if(next <= 1000001)
				semip.push_back(next);
			else
				break;
		}
	}
	sort(semip.begin(), semip.end());
	vector<int>::iterator it = unique(semip.begin(), semip.end());
	semip.resize(distance(semip.begin(), it));
	int n;
	while(EOF != scanf("%d", &n)){
		if(n == 0) break;
		int i = upper_bound(semip.begin(), semip.end(), n)-semip.begin();

		printf("%d %d\n", n, i);
	}
	return 0;
}