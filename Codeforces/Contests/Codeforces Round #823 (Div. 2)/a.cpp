#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=100;
const I A=100;

I cnts[A+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,c;cin>>n>>c;
    fill_n(cnts,A+1,0);
    for(I i=0;i<n;i++){
      I a;cin>>a;
      cnts[a]++;
    }
    I res=0;
    for(I i=0;i<=A;i++)
      res+=min(cnts[i],c);
    printf("%i\n",res);
  }
}