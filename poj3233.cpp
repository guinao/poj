#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> vec;
typedef vector<vec> mat;

int m;

mat mul(mat &a, mat &b)
{
	mat c(a.size(), vec(b[0].size()));
	for(int i=0; i<a.size(); ++i){
		for(int j=0; j<b[0].size(); ++j){
			for(int k=0; k<b.size(); ++k){
				c[i][j] = (c[i][j]+a[i][k]*b[k][j]) % m;
			}
		}
	}
	return c;
}

mat pow(mat &a, int p)
{
	mat ret(a.size(), vec(a.size()));
	for(int i=0; i<(int)a.size(); ++i)
		ret[i][i] = 1;
	while(p > 0){
		if(p & 1)
			ret = mul(a, ret);
		a = mul(a, a);
		p >>= 1;
	}
	return ret;
}

int main()
{
	int n, k;
	int x;
	while(EOF != scanf("%d %d %d", &n, &k, &m)){
		mat a(n*2, vec(n*2));
		for(int i=0; i<n; ++i){
			for(int j=0; j<n; ++j){
				scanf("%d", &x);
				a[i][j] = x;
			}
			a[n+i][i] = 1;
			a[n+i][n+i] = 1;
		}
		a = pow(a, k+1);
		for(int i=0; i<n; ++i){
			for(int j=0; j<n; ++j){
				int t = a[n+i][j];
				if(i == j) t = (t+m-1) % m;
				printf("%d%c", t, j+1==n? '\n': ' ');
			}
		}
	}
	return 0;
}