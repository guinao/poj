#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int mod = 10007;
typedef vector<int> vec;
typedef vector<vec> mat;

mat mul(mat &a, mat &b){
	mat c(a.size(), vec(b[0].size()));
	for(int i=0; i<(int)a.size(); ++i){
		for(int j=0; j<(int)b[0].size(); ++j){
			for(int k=0; k<(int)b.size(); ++k){
				c[i][j] = (c[i][j] + a[i][k]*b[k][j]) % mod;
			}
		}
	}
	return c;
}

mat pow(mat &a, int n){
	mat ret(a.size(), vec(a.size()));
	for(int i=0; i<(int)ret.size(); ++i)
		ret[i][i] = 1;
	while(n > 0){
		if(n & 1)
			ret = mul(ret, a);
		a = mul(a, a);
		n >>= 1;
	}
	return ret;
}

int main()
{
	int t, n;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		mat m(3, vec(3));
		m[0][0] = 2; m[0][1] = 1; m[0][2] = 0;
		m[1][0] = 2; m[1][1] = 2; m[1][2] = 2;
		m[2][0] = 0; m[2][1] = 1; m[2][2] = 2;
		m = pow(m, n);
		printf("%d\n", m[0][0]);
	}
	return 0;
}