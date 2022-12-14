#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    Lli d,m;cin>>d>>m;
    Lli res=0;
    for(I i=0;(1ll<<i)<=d;i++)(res+=(res+1)*(min((1ll<<(i+1))-1,d)-(1ll<<i)+1))%=m;
    printf("%lli\n",res);
  }
}