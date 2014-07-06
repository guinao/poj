#include<cstdio>
#include<vector>
#include<queue>
#include<cmath>
#include<algorithm>
using namespace std;

int main()
{
	int n;
	double x, y;
	priority_queue<double> pq;
	scanf("%d", &n);
	for(int i=0; i<n; ++i){
		scanf("%lf", &x);
		pq.push(x);
	}
	while(pq.size() > 1){
		x = pq.top();
		pq.pop();
		y = pq.top();
		pq.pop();
		pq.push(2 * sqrt(x*y));
	}
	printf("%.3f", pq.top());
	return 0;
}