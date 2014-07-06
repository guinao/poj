#include<cstdio>
#include<algorithm>
using namespace std;

int main()
{
	int a[6], judge;
	int rest;
	while(true){
		judge = 0;
		for(int i=0; i<6; ++i){
			scanf("%d", &a[i]);
			judge += a[i];
		}
		if(judge == 0)
			break;
		int ans = a[5];
		ans += a[4];
		a[0] -= min(a[0], 11*a[4]);
		ans += a[3];
		rest = 5*a[3];
		if(a[1] >= rest)
			a[1] -= rest;
		else{
			rest -= a[1];
			a[1] = 0;
			a[0] -= min(a[0], 4*rest);
		}
		ans += (a[2]+3)/4;
		switch(a[2]%4){
		case 0:
			rest = 0;
			break;
		case 1:
			rest = 7;
			if(a[1] >= 5)
				a[1] -= 5;
			else{
				rest += (5-a[1])*4;
				a[1] = 0;
			}
			break;
		case 2:
			rest = 6;
			if(a[1] >= 3)
				a[1] -= 3;
			else{
				rest += (3-a[1])*4;
				a[1] = 0;
			}
			break;
		case 3:
			rest = 5;
			if(a[1] >= 1)
				a[1] -= 1;
			else{
				rest += (1-a[1])*4;
				a[1] = 0;
			}
			break;
		}
		a[0] -= min(a[0], rest);
		ans += (a[1]+8)/9;
		rest = a[1] % 9;
		if(rest != 0)
			a[0] -= min(a[0], (9-rest)*4);
		ans += (a[0]+35)/36;
		printf("%d\n", ans);
	}
	return 0;
}