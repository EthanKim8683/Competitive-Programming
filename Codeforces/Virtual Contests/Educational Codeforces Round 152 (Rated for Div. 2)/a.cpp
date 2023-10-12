#include<bits/stdc++.h>
using namespace std;
using I=int;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I b,c,h;cin>>b>>c>>h,b--;
    printf("%i\n",1+min(b,c+h)*2);
  }
}