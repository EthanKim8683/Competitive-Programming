#include<bits/stdc++.h>

using namespace std;

using I=int;

const I MAX=1e9;

I cei(I a,I b){
  return a/b+!!(a%b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,d;cin>>n>>d;
    I x=(n-1)/2;
    I res=MAX;
    if(x-1>=0)res=min(res,(x-1)+cei(d,(x-1)+1));
    res=min(res,(x+0)+cei(d,(x+0)+1));
    res=min(res,(x+1)+cei(d,(x+1)+1));
    printf("%s\n",res<=n?"YES":"NO");
  }
}