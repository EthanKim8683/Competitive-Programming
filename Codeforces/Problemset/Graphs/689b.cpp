#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

using I=int;

const I N=200000;
const I MAX=1e9;

vector<I>adjs[N];
I diss[N];
queue<I>que;

void add(I i,I d){
  if(d>=diss[i])return;
  diss[i]=d;
  que.push(i);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(diss,n,MAX);
  for(I i=0;i<n;i++){I a;cin>>a;adjs[i].push_back(a-1);}
  for(I i=0;i<n;i++){
    if(i-1>=0)adjs[i].push_back(i-1);
    if(i+1<n)adjs[i].push_back(i+1);
  }
  add(0,0);
  while(que.size()){
    I a=que.front();que.pop();
    for(auto b:adjs[a])add(b,diss[a]+1);
  }
  for(I i=0;i<n;i++)printf("%i ",diss[i]);
  return 0;
}