#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

bool mark[10];
int v[10];
int cnt;

int solve(int l)
{
	int ans = 999999999;
	vector<int> v1,v2;
	for(int i=0; i<l; ++i){
		if(mark[i])
			v1.push_back(v[i]);
		else
			v2.push_back(v[i]);
	}
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	bool mark[10];
	do{
		if(v1[0]==0 && v1.size()!=1)
			continue;
		int na = 0;
		int base = 1;
		int len = v1.size();
		for(int i=0; i<len; ++i){
			base *= 10;
			na = na*10 + v1[i];
		}
		memset(mark, false, sizeof mark);
		if(v1.size() < v2.size()){
			int nb = 0;
			for(int i=0; i<(int)v2.size(); ++i){
				if(v2[i] > 0){
					nb = v2[i];
					mark[i] = true;
					break;
				}
			}
			for(int i=0; i<(int)v2.size(); ++i)
				if(!mark[i])
					nb = nb*10 + v2[i];
			ans = min(ans, nb-na);
		}else{
			int nb = 0;
			int index = -1;
			for(int i=0; i<(int)v2.size(); ++i){
				if(v2[i]>v1[0]){
					index = i;
					break;
				}
			}
			if(index == -1)
				continue;
			mark[index] = true;
			nb = v2[index];
			for(int i=0; i<(int)v2.size(); ++i){
				if(!mark[i])
					nb = nb*10 + v2[i];
			}
			ans = (ans, nb - na);
		}
	}while(next_permutation(v1.begin(), v1.end()));
	return ans;
}

int dfs(int a, int b, int len)
{
	int ret = 999999999;
	if(b == 0){
		ret = solve(len);
	}
	else if(len - a == b){
		for(int i=a; i<len; ++i){
			mark[i] = true;
		}
		ret = solve(len);
		for(int i=a; i<len; ++i){
			mark[i] = false;
		}
	}
	else{
		mark[a] = true;
		ret = min(ret, dfs(a+1, b-1, len));
		mark[a] = false;
		ret = min(ret, dfs(a+1, b, len));
	}
	return ret;
}

int main()
{
	int n;
	char buf[32];
	scanf("%d", &n);
	getchar();
	while(n--){
		gets(buf);
		for(int i=0, j=0; i<strlen(buf); i+=2, ++j){
			v[j] = buf[i] - '0';
			mark[j] = false;
		}
		cnt = 0;
		printf("%d\n", dfs(0, (strlen(buf)+1)/4, (strlen(buf)+1)/2));
	}
	return 0;
}