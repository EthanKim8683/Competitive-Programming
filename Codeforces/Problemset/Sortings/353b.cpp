#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100;
const I A=99;
I a_arr[2*N];
I viss[A+1];
vector<I>rems;
I ress[2*N];
I inds[2*N];
I cnts[2];
B cmp(I a,I b){
  return a_arr[a]<a_arr[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<2*n;i++)cin>>a_arr[i];
  iota(inds,inds+2*n,0);
  sort(inds,inds+2*n,cmp);
  I t=0;
  for(I i=0;i<2*n;i++){
    I j=inds[i],a=a_arr[j];
    if(viss[a]==0){
      ress[j]=t,cnts[t]++,t=!t;
      viss[a]=1;
      continue;
    }
    if(viss[a]==1){
      ress[j]=t,cnts[t]++,t=!t;
      viss[a]=2;
      continue;
    }
    rems.push_back(j);
  }
  for(auto i:rems)ress[i]=t,t=!t;
  printf("%i\n",cnts[0]*cnts[1]);
  for(I i=0;i<2*n;i++)printf("%i ",ress[i]+1);
}