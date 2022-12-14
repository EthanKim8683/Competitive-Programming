#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=int64_t;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k;cin>>k;
  while(k--){
    I n,x,t;cin>>n>>x>>t;
    I hgt=t/x;
    I tri=min(hgt,n);
    I wdt=max(n-tri,0);
    printf("%lli\n",(Lli)wdt*hgt+(Lli)tri*(tri-1)/2);
  }
}