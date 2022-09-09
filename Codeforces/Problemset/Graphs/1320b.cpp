#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;
const I K=N;
const I MAX=1e9;

vector<I>adjs1[N];
vector<I>adjs2[N];
I p_arr[K];
queue<I>que;
I diss[N];

void add(I i,I d){
  if(d>=diss[i])return;
  que.push(i),diss[i]=d;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill_n(diss,n,MAX);
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs1[u].push_back(v);
    adjs2[v].push_back(u);
  }
  I k;cin>>k;
  for(I i=0;i<k;i++){I p;cin>>p,p_arr[i]=p-1;}
  add(p_arr[k-1],1);
  while(que.size()){
    I a=que.front();que.pop();
    for(auto b:adjs2[a])add(b,diss[a]+1);
  }
  I low=0,upp=0;
  for(I i=0;i<k-1;i++){
    I a=p_arr[i],b=p_arr[i+1];
    I sht=MAX;
    B cnt=0;
    for(auto c:adjs1[a]){
      if(diss[c]<sht)sht=diss[c],cnt=0;
      if(b!=c)cnt+=diss[c]==sht;
    }
    low+=diss[b]!=sht;
    upp+=cnt;
  }
  printf("%i %i\n",low,upp);
  return 0;
}