#include<bits/stdc++.h>
using namespace std;
using I=int;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    printf("%s\n",(n+m)%2?"Burenka":"Tonya");
  }
}