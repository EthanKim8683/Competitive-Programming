#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=1e6;
const Lli MOD=(1ll<<31)-1;
const Lli BAS=(1ll<<17)-1;
Lli pows[N+1];
Lli hshs[N+1];
void bld(S s){
  for(I i=0;i<s.size();i++)hshs[i+1]=(hshs[i]*BAS+s[i])%MOD;
}
Lli qry(I l,I r){
  return((hshs[r]-hshs[l]*pows[r-l])%MOD+MOD)%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  pows[0]=1;
  for(I i=0;i<N;i++)pows[i+1]=pows[i]*BAS%MOD;
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    bld(s);
    I n=s.size(),res=0,pre=1;
    for(I l1=0,l2=1,r1=n,r2=n-1;l2<=r2;l2++,r2--)qry(l1,l2)==qry(r2,r1)?l1=l2,r1=r2,res+=2,pre=0:pre=1;
    pre|=n%2;
    printf("%i\n",res+pre);
  }
}