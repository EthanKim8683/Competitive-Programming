#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1e6;
const Lli MOD=1e9+7;
I k_arr[N];
map<I,I>cnts;
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,p;cin>>n>>p;
    for(I i=0;i<n;i++)cin>>k_arr[i];
    if(p==1){printf("%i\n",n%2);continue;}
    cnts.clear();
    for(I i=0;i<n;i++)cnts[k_arr[i]]++;
    Lli res=0;B rem=0;
    while(cnts.size()){
      auto it=prev(cnts.end());
      auto[k,cnt]=*it;cnts.erase(it);
      if(rem){(res-=cnt*mpw(p,k))%=MOD;continue;}
      if(cnt%2==0)continue;
      B fnd=0;
      for(Lli t=k,req=cnt%2;(t-=1)>=0&&(req*=p)<=n;){
        if(cnts.find(t)==cnts.end())continue;
        I dif=min((I)req,cnts[t]);
        if((req-=dif)==0){fnd=1;break;}
      }
      if(!fnd){(res+=mpw(p,k))%=MOD,rem=1;continue;}
      for(Lli t=k,req=cnt%2;(t-=1)>=0&&(req*=p)<=n;){
        if(cnts.find(t)==cnts.end())continue;
        I dif=min((I)req,cnts[t]);cnts[t]-=dif;
        if((req-=dif)==0)break;
      }
    }
    printf("%lli\n",(res+MOD)%MOD);
  }
}