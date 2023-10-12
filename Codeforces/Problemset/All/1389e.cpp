#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I m,d,w;cin>>m>>d>>w;
    Lli cnt=min(m,d),fac=w/gcd(d-1,w),low=cnt/fac;
    printf("%lli\n",low*(low-1)/2*fac+(cnt-fac*low)*low);
  }
}