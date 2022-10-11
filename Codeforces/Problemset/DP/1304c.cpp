#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    I n,m;cin>>n>>m;
    Lli tim=0,low=m,upp=m;
    B res=1;
    for(I i=0;i<n;i++){
      Lli t,l,h;cin>>t>>l>>h;
      Lli dif=t-tim;
      low-=dif,upp+=dif;
      low=max(low,l);
      upp=min(upp,h);
      tim=t;
      res&=low<=upp;
    }
    printf("%s\n",res?"YES":"NO");
  }
}