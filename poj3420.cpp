#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> vec;
typedef vector<vec> mat;

const int maxn = 4;
int n, m;
mat mm(1<<maxn, vec(1<<maxn));

mat mul(mat &a, mat &b)
{
	mat c(a.size(), vec(b[0].size()));
	for(int i=0; i<(int)a.size(); ++i){
		for(int j=0; j<(int)b[0].size(); ++j){
			for(int k=0; k<(int)b.size(); ++k){
				c[i][j] = (c[i][j]+a[i][k]*b[k][j]) % m;
			}
		}
	}
	return c;
}

mat pow(mat a, int p)
{
	mat ret(a.size(), vec(a.size()));
	for(int i=0; i<(int)ret.size(); ++i)
		ret[i][i] = 1;
	while(p > 0){
		if(p & 1) ret = mul(ret, a);
		a = mul(a, a);
		p >>= 1;
	}
	return ret;
}

void dfs(int s, int ns, int i)
{
	if(i == maxn){
		mm[ns][s] = 1;
		return;
	}
	if(s & 1<<i){
		dfs(s, ns, i+1);
		if(i && !(ns&1<<(i-1)))
			dfs(s, ns|3<<(i-1), i+1);
	}else{
		dfs(s, ns|1<<i, i+1);
	}
}

int main()
{
	int n;
	for(int i=0; i<1<<maxn; ++i)
		dfs(i, 0, 0);
	while(EOF != scanf("%d %d", &n, &m)){
		if(n==0 && m==0) break;
		mat ans = pow(mm, n);
		printf("%d\n", ans[15][15]);
	}
	return 0;
}