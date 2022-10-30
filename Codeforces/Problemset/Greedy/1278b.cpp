#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I a,b;cin>>a>>b;
    I rem=abs(a-b),res=0;
    while(rem>0||rem%2)rem-=++res;
    printf("%i\n",res);
  }
}