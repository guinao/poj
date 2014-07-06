#include <cstdio>
#include <cstring>
using namespace std;

char name[32768][256];

int main()
{
	int n;
	double l, v;
	double maxt, t;
	int dir, cnt;
	char buf[1024];
	while(EOF != scanf("%d", &n)){
		if(n == 0) break;
		scanf("%lf %lf\n", &l, &v);
		dir = 0;
		maxt = -1;
		cnt = 0;
		for(int i=0; i<n; ++i){
			gets(buf);
			double pos;
			sscanf(buf+2, "%lf %s", &pos, name[i]);
			if(buf[0] == 'p' || buf[0] == 'P'){
				t = (l-pos) / v;
			}else{
				t = pos / v;
				++cnt;
			}
			if(t > maxt){
				maxt = t;
				if(buf[0]=='p' || buf[0] == 'P')
					dir = 1;
				else
					dir = 0;
			}
		}
		if(dir == 0)
			printf("%13.2f %s\n", (int)(maxt*100)/100.0, name[cnt-1]);
		else
			printf("%13.2f %s\n", (int)(maxt*100)/100.0, name[cnt]);
	}
	return 0;
}