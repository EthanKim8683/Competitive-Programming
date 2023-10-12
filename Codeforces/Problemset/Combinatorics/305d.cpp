#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1e6;
const Lli MOD=1e9+7;
const I MAX=1e9;
const I MIN=-MAX;
B adjs[N];
I fens[N+1];
I n;
void upd(I i,I val){
  for(;i<=n;i+=i&-i)fens[i]+=val;
}
I qry(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m,k;cin>>n>>m>>k;
  I l=MAX,r=MIN;
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    if(v==u+1)continue;
    if(v!=u+1+k)printf("0"),exit(0);
    adjs[u]=1,upd(u+1,1);
    l=min(l,u),r=max(r,u+1);
  }
  if(r-l>k+1)printf("0"),exit(0);
  Lli res=1;
  for(I i=0;i<n-k-1;i++){
    I j=j=min(n-1-k,i+k+1);
    if(qry(i)-qry(0)>0||qry(n)-qry(j)>0)continue;
    I rem=(j-(i+1))-(qry(j)-qry(i+1));
    if(adjs[i]){
      (res+=mpw(2,rem)-1)%=MOD;
    }else{
      (res+=mpw(2,rem))%=MOD;
    }
  }
  printf("%lli\n",(res+MOD)%MOD);
}
/*
1. every vertex must have an edge to i + 1
2. only a range of vertices j in [i, i + k + 1) may have edges to j + k + 1
*/