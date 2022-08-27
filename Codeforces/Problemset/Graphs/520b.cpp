#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>

using namespace std;

using I=int;

const I M=10000;
const I MAX=1e9;

queue<I>que;
I deps[2*M];

void add(I a,I d){
  if(d>=deps[a])return;
  que.push(a),deps[a]=d;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill_n(deps,2*max(n,m),MAX);
  add(n,0);
  while(!que.empty()){
    I a=que.front();que.pop();
    I d=deps[a];
    if(a==m){printf("%i\n",d);return 0;}
    if(a<m)add(a*2,d+1);
    if(a>0)add(a-1,d+1);
  }
  return 0;
}