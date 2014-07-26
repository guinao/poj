#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef vector<ll> vec;
typedef vector<vec> mat;

mat mul(mat &a, mat &b)
{
	mat c(a.size(), vec(b[0].size()));
	for(int i=0; i<(int)a.size(); ++i){
		for(int k=0; k<(int)b.size(); ++k)if(a[i][k]!=0){
			for(int j=0; j<(int)b[0].size(); ++j){
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return c;
}

mat pow(mat &a, int m)
{
	mat ret(a.size(), vec(a.size()));
	for(int i=0; i<(int)ret.size(); ++i)
		ret[i][i] = 1;
	while(m > 0){
		if(m & 1) ret = mul(ret, a);
		a = mul(a, a);
		m >>= 1;
	}
	return ret;
}

int main()
{
	int n, m, k;
	char buf[4];
	int x, y;
	while(EOF != scanf("%d %d %d", &n, &m, &k)){
		if(n==0 && m==0 && k==0) break;
		mat a(n+1, vec(n+1));
		for(int i=0; i<(int)a.size(); ++i)
			a[i][i] = 1;
		for(int i=0; i<k; ++i){
			scanf("%s", buf);
			if(buf[0] == 'g'){
				scanf("%d", &x);
				a[x-1][n] += 1;
			}else if(buf[0] == 'e'){
				scanf("%d", &x);
				fill(a[x-1].begin(), a[x-1].end(), 0);
			}else{
				scanf("%d %d", &x, &y);
				if(x != y)
					swap(a[x-1], a[y-1]);
			}
		}
		a = pow(a, m);
		for(int j=0; j<n-1; ++j){
			printf("%lld ", a[j][n]);
		}
		printf("%lld\n", a[n-1][n]);
	}
	return 0;
}
