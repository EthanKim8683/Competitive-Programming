#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;
const I MAX=1e9;

vector<I>adjs[N];
I a_arr[N];
I inds[N];
I acts[N];
B viss[N];
queue<I>que;

void add(I i){
  if(viss[i])return;
  que.push(i),viss[i]=true;
}

B cmp(I a,I b){
  return inds[a]<inds[b];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  for(I i=0;i<n;i++){I a;cin>>a,a_arr[i]=a-1;}
  for(I i=0;i<n;i++)inds[a_arr[i]]=i;
  add(0);
  I i=0;
  while(que.size()){
    I a=que.front();que.pop();
    acts[i++]=a;
    sort(adjs[a].begin(),adjs[a].end(),cmp);
    for(auto b:adjs[a])add(b);
  }
  B res=true;
  for(I i=0;i<n;i++)res&=acts[i]==a_arr[i];
  if(res)printf("Yes\n");
  else printf("No\n");
  return 0;
}