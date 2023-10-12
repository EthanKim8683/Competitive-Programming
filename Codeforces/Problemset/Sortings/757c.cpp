#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I M=1e6;
const Lli X=9973;
const Lli Y=(1ll<<61)-1;
const Lli MOD=1e9+7;
vector<I>gyms[N];
I pres[M];
Lli hshs[M];
map<Lli,I>cnts;
Lli facs[M+1];
__int128 mul(Lli a,Lli b){
  return(__int128)a*b;
}
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=Y;y;y>>=1,x=mul(x,x)%Y)if(y&1)res=mul(res,x)%Y;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++){
    I g;cin>>g;
    cnts.clear();
    for(I j=0;j<g;j++){
      I t;cin>>t,t--;
      cnts[t]++;
    }
    for(auto[j,cnt]:cnts)hshs[j]=(mul(hshs[j],mpw(X,i-pres[j]))+cnt)%Y,pres[j]=i;
  }
  for(I i=0;i<m;i++)hshs[i]=mul(hshs[i],mpw(X,n-1-pres[i]))%Y;
  cnts.clear();
  for(I i=0;i<m;i++)cnts[hshs[i]]++;
  facs[0]=1;
  for(I i=1;i<=m;i++)facs[i]=facs[i-1]*i%MOD;
  Lli res=1;
  for(auto[hsh,cnt]:cnts)(res*=facs[cnt])%=MOD;
  printf("%lli\n",(res+MOD)%MOD);
}