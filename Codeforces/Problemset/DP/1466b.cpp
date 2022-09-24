#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

B viss[2*N+1+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    fill_n(viss,2*n+1+1,0);
    I res=0;
    for(I i=0;i<n;i++){
      I x;cin>>x;
      x+=viss[x];
      res+=!viss[x];
      viss[x]=1;
    }
    printf("%i\n",res);
  }
}