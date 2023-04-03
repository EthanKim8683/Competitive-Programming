#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using S=string;
using B=bool;
const I N=1e6;
const Lli MOD=(1ll<<31)-1;
const Lli BAS=(1ll<<17)-1;
Lli pows[N+1];
Lli hshs[N+1];
I n;
void bld(S s){
  pows[0]=1;
  for(I i=1;i<=n;i++)pows[i]=pows[i-1]*BAS%MOD;
  for(I i=1;i<=n;i++)hshs[i]=(hshs[i-1]*BAS+s[i-1])%MOD;
}
Lli qry(I l,I r){
  return((hshs[r]-pows[r-l]*hshs[l])%MOD+MOD)%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  n=s.size();
  bld(s);
  for(I i=1;i<=n;i++){
    B vld=1;
    for(I j=0;j<n;j+=i){
      I l=min(j+i,n)-j;
      vld&=qry(j,j+l)==qry(0,l);
    }
    if(vld)printf("%i ",i);
  }
}