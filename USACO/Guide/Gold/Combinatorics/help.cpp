#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const Lli MOD=1e9+7;
pair<I,I>rngs[N];
Lli fens[2][2*N+1];
Lli pows[N+1];
I n;
void upd(I t,I i,Lli val){
  for(;i<=2*n;i+=i&-i)(fens[t][i]+=val)%=MOD;
}
Lli qry(I t,I i){
  Lli res=0;
  for(;i>0;i-=i&-i)(res+=fens[t][i])%=MOD;
  return res;
}
I main(){
#ifndef ETHANKIM8683
  freopen("help.in","r",stdin);
  freopen("help.out","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  pows[0]=1;
  for(I i=1;i<=N;i++)pows[i]=pows[i-1]*2%MOD;
  cin>>n;
  for(I i=0;i<n;i++){
    I l,r;cin>>l>>r,l--,r--;
    rngs[i]={l,r};
  }
  sort(rngs,rngs+n);
  for(I i=0;i<n;i++){
    auto[l,r]=rngs[i];
    upd(0,r+1,qry(0,2*n)-qry(0,l)+qry(0,l)+pows[qry(1,l)]);
    upd(1,r+1,1);
  }
  printf("%lli\n",qry(0,2*n));
}