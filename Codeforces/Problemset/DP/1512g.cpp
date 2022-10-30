#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

const I C=1e7;
const Lli MAX=1e18;

Lli dp1[C+1];
Lli dp2[C+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill_n(dp2,C+1,-1);
  for(I i=1;i<=C;i++)for(I j=i;j<=C;j+=i)dp1[j]+=i;
  for(I i=C;i>=1;i--)if(dp1[i]<=C)dp2[dp1[i]]=i;
  I t;cin>>t;
  while(t--){
    I c;cin>>c;
    printf("%lli\n",dp2[c]);
  }
}