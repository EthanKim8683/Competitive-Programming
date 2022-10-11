#include<bits/stdc++.h>

using namespace std;

using I=int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I a1,a2,a3,a4;cin>>a1>>a2>>a3>>a4;
    I res=0;
    res=max(res,min(a1,a2)*min(a3,a4));
    res=max(res,min(a1,a3)*min(a2,a4));
    res=max(res,min(a1,a4)*min(a2,a3));
    printf("%i\n",res);
  }
}