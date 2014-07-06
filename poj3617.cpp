#include<cstdio>
#include<cstring>

int main()
{
	int n;
	char s[2048], rs[2048], t[2048];
	scanf("%d", &n);
	for(int i=0; i<n; ++i){
		getchar();
		s[i] = getchar();
	}
	for(int i=0; i<n; ++i){
		rs[i] = s[n-i-1];
	}
	rs[n] = '\0';
	int l=0, r=0;
	for(int i=0; i<n; ++i){
		if(strcmp(s+l, rs+r) < 0)
			t[i] = s[l++];
		else
			t[i] = rs[r++];
	}
	t[n] = '\0';
	for(int i=0; t[i]!=0; ++i){
		if(i>0 && i%80==0)
			putchar('\n');
		putchar(t[i]);
	}
	return 0;
}