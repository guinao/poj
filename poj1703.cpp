#include <cstdio>
#include <cstring>

const int maxn = 100100;

struct Disjoint_Set{
	int p[maxn*2];
	int r[maxn*2];
	int n;

	void makeset(int n){
		this->n = n;
		for(int i=1; i<=n*2; ++i){
			p[i] = i;
			r[i] = 0;
		}
	}

	int findparent(int x){
		if(p[x] != x){
			p[x] = findparent(p[x]);
		}
		return p[x];
	}

	bool issame(int a, int b){
		return findparent(a) == findparent(b);
	}

	bool isdiff(int a, int b){
		return findparent(a+n) == findparent(b);
	}

	void link(int a, int b){
		a = findparent(a);
		b = findparent(b);
		if(a != b){
			if(r[a] < r[b])
				p[b] = a;
			else{
				p[a] = b;
				if(r[a] == r[b])
					r[a]++;
			}
		}
	}

	void dlink(int a, int b){
		link(a+n, b);
		link(a, b+n);
	}
}dset;

int main()
{
	int t, a, b;
	int n, m;
	char buf[32];
	scanf("%d", &t);
	while(t--){
		scanf("%d %d\n", &n, &m);
		dset.makeset(n);
		for(int i=0; i<m; ++i){
			gets(buf);
			sscanf(buf+2, "%d %d", &a, &b);
			if(buf[0] == 'A'){
				if(dset.issame(a, b))
					puts("In the same gang.");
				else if(dset.isdiff(a, b))
					puts("In different gangs.");
				else
					puts("Not sure yet.");
			}
			else{
				dset.dlink(a, b);
			}
		}
	}
	return 0;
}