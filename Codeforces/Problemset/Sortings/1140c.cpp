#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=3e5;
const I T=1e6;
pair<I,I>sngs[N];
Lli fens[2][T+2];
I k;
void upd(I i,I j,I val){
  for(;j<=T+1;j+=j&-j)fens[i][j]+=val;
}
Lli qry(I i,I j){
  Lli res=0;
  for(;j>0;j-=j&-j)res+=fens[i][j];
  return res;
}
I fnd(){
  I l=0,r=T+1;
  while(l<r){
    I m=l+(r-l)/2;
    qry(0,T+1)-qry(0,m)<=k-1?r=m:l=m+1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n>>k;
  for(I i=0;i<n;i++){
    I t,b;cin>>t>>b;
    sngs[i]={b,t};
  }
  sort(sngs,sngs+n);
  for(I i=0;i<n;i++){
    auto[b,t]=sngs[i];
    upd(0,t+1,1);
    upd(1,t+1,t);
  }
  Lli res=0;
  for(I i=0;i<n;i++){
    auto[b,t]=sngs[i];
    upd(0,t+1,-1);
    upd(1,t+1,-t);
    I j=fnd(),rem=min(k-1-(qry(0,T+1)-qry(0,j)),qry(0,j)-qry(0,j-1));
    res=max(res,((Lli)rem*(j-1)+qry(1,T+1)-qry(1,j)+t)*b);
  }
  printf("%lli\n",res);
}