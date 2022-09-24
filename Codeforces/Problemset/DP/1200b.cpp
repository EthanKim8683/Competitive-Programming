#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=100;

I h_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m,k;cin>>n>>m>>k;
    I h1;cin>>h1;
    B res=1;
    for(I i=1;i<n;i++){
      I h2;cin>>h2;
      if(h2-k>h1)m-=h2-k-h1;
      else m+=h1-max(h2-k,0);
      res&=m>=0;
      h1=h2;
    }
    printf("%s\n",res?"YES":"NO");
  }
}