#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
const I N=100000;
pair<I,I>rngs[N];
Lf facs[N];
pair<Lf,Lf>dp[N][2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,p;cin>>n>>p;
  for(I i=0;i<n;i++){
    I l,r;cin>>l>>r;
    rngs[i]={l,r};
  }
  for(I i=0;i<n;i++){
    auto[l,r]=rngs[i];
    I num=r/p-(l-1)/p;
    I den=r-l+1;
    facs[i]=(Lf)num/den;
  }
  // x' = x + (1 + y) * d, y' = y + d
  dp[0][1]={facs[0],facs[0]};
  for(I i=1;i<n;i++){
    
  }
}