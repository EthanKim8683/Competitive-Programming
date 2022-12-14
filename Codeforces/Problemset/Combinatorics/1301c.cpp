#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    Lli n,m;cin>>n>>m;
    I rem=n-m,cnt=m+1;
    Lli res=n*(n+1)/2;
    Lli div=rem/cnt;
    Lli del=div*(div+1)/2;
    Lli mod=rem%cnt;
    Lli edg=div+1;
    Lli ext=edg*(edg+1)/2;
    res-=del*(cnt-mod);
    res-=ext*mod;
    printf("%lli\n",res);
  }
}