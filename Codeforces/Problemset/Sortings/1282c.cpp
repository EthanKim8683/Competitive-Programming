#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
pair<I,I>prbs[N];
I rems[2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>m;
  while(m--){
    I n,t,a,b;cin>>n>>t>>a>>b;
    for(I i=0;i<n;i++)cin>>prbs[i].second;
    for(I i=0;i<n;i++)cin>>prbs[i].first;
    sort(prbs,prbs+n);
    fill_n(rems,2,0);
    for(I i=0;i<n;i++)rems[prbs[i].second]++;
    Lli req=0,vis=0,res=0;
    auto app=[&](I upp){
      Lli rem=upp-req;
      if(rem<0)return;
      Lli ict1=min(rem/a,(Lli)rems[0]);
      Lli ict2=min((rem-ict1*a)/b,(Lli)rems[1]);
      res=max(res,vis+ict1+ict2);
    };
    for(I i=0;i<n;i++){
      auto[tim,dif]=prbs[i];
      app(tim-1);
      req+=dif?b:a,rems[dif]--,vis++;
    }
    app(t);
    printf("%lli\n",res);
  }
}