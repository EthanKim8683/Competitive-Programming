#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using S=string;
const I L=19;
Lli facs[L+1];
I cnts[10];
I curs[10];
Lli res=0;
void dfs(I i=0){
  if(i==10){
    I tot=accumulate(curs,curs+10,0);
    Lli cur=facs[tot];
    for(I k=0;k<10;k++)cur/=facs[curs[k]];
    res+=cur;
    if(curs[0]>0){
      Lli cur=facs[tot-1]/facs[curs[0]-1];
      for(I k=1;k<10;k++)cur/=facs[curs[k]];
      res-=cur;
    }
    return;
  }
  for(I j=min(1,cnts[i]);j<=cnts[i];j++)curs[i]=j,dfs(i+1);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=L;i++)facs[i]=facs[i-1]*i;
  S n;cin>>n;
  for(auto c:n)cnts[c-'0']++;
  dfs();
  printf("%lli\n",res);
}
/*
we can brute force for possible number counts
*/