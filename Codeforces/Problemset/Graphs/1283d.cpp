#include<iostream>
#include<cstdio>
#include<map>
#include<queue>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;
const I M=2e5;

I x_arr[N];
map<I,I>viss;
queue<I>que;
I ress[M];

void add(I i,I d){
  if(viss.find(i)!=viss.end())return;
  que.push(i),viss.insert({i,d});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>x_arr[i];
  for(I i=0;i<n;i++)viss.insert({x_arr[i],0});
  for(I i=0;i<n;i++){
    I x=x_arr[i];
    add(x-1,1),add(x+1,1);
  }
  I cnt=0;
  Lli res=0;
  while(que.size()){
    I a=que.front();que.pop();
    I d=viss[a];
    res+=d;
    ress[cnt++]=a;
    if(cnt==m)break;
    add(a-1,d+1),add(a+1,d+1);
  }
  printf("%lli\n",res);
  for(I i=0;i<m;i++)printf("%i ",ress[i]);
  return 0;
}