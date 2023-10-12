#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const Lli MOD=998244353;
tuple<I,I,I>pors[N];
vector<I>cpss;
Lli fens[2*N+1];
Lli ress[2*N+1];
I n;
void upd(I i,Lli val){
  for(;i<=cpss.size()-1;i+=i&-i)(fens[i]+=val)%=MOD;
}
Lli qry(I i){
  Lli res=0;
  for(;i>0;i-=i&-i)(res+=fens[i])%=MOD;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++){
    I x,y,s;cin>>x>>y>>s;
    pors[i]={x,y,s};
    cpss.push_back(x),cpss.push_back(y);
  }
  cpss.push_back(0);
  cpss.push_back(get<0>(pors[n-1])+1);
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i+1<cpss.size();i++)upd(i+1,ress[i]=(cpss[i+1]-cpss[i])%MOD);
  for(I i=0;i<n;i++){
    auto[x,y,s]=pors[i];
    x=lower_bound(cpss.begin(),cpss.end(),x)-cpss.begin();
    y=lower_bound(cpss.begin(),cpss.end(),y)-cpss.begin();
    Lli dif=(qry(x)-qry(y))%MOD;
    if(s)(ress[x]+=dif)%=MOD;
    upd(x+1,dif);
  }
  Lli res=0;
  for(I i=0;i+1<cpss.size();i++)(res+=ress[i])%=MOD;
  printf("%lli\n",(res+MOD)%MOD);
}