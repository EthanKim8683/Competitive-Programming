#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=2e5;

I a_arr[N];
pair<I,Lli>adjs[N*2];
B viss1[N*2],viss2[N*2];
Lli vals[N*2];
B vlds[N*2];
I n;

void add(I i,Lli j,Lli c){
  if(j<0||j>=n*2)j=-1;
  adjs[i]={j,c};
}

B dfs(I a){
  if(viss1[a])return 0;
  if(viss2[a])return vlds[a];
  viss1[a]=viss2[a]=1;
  vlds[a]=1;
  auto[b,c]=adjs[a];
  if(b!=-1)vlds[a]&=dfs(b),vals[a]=vals[b]+c;
  else vals[a]=c;
  viss1[a]=0;
  return vlds[a];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=1;i<n;i++)cin>>a_arr[i];
  for(I i=1;i<n;i++){
    I a=a_arr[i];
    add(i*2+1,(i+a)*2,a),add(i*2,(i-a)*2+1,a);
  }
  viss2[0*2]=viss2[0*2+1]=1;
  for(I i=1;i<n;i++){
    if(dfs(i*2))printf("%lli\n",vals[i*2]+i);
    else printf("-1\n");
  }
  return 0;
}