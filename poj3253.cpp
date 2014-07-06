#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

typedef long long ll;

int main()
{
	int n, li;
	ll sum;
	priority_queue<int, vector<int>, greater<int> > pq;
	scanf("%d", &n);
	for(int i=0; i<n; ++i){
		scanf("%d", &li);
		pq.push(li);
	}
	sum = 0;
	while(pq.size() > 1){
		int t = pq.top();
		pq.pop();
		t += pq.top();
		pq.pop();
		sum += t;
		pq.push(t);
	}
	printf("%lld\n", sum);
	return 0;
}