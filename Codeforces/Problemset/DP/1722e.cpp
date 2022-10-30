#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I H=1000;
const I W=1000;

Lli ps[H+1][W+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,q;cin>>n>>q;
    for(I i=0;i<=H;i++)for(I j=0;j<=W;j++)ps[i][j]=0;
    for(I i=0;i<n;i++){
      I h,w;cin>>h>>w;
      ps[h][w]+=h*w;
    }
    for(I i=1;i<=H;i++)for(I j=1;j<=W;j++)ps[i][j]+=ps[i-1][j]+ps[i][j-1]-ps[i-1][j-1];
    while(q--){
      I hs,ws,hb,wb;cin>>hs>>ws>>hb>>wb,hb--,wb--;
      printf("%lli\n",ps[hb][wb]-ps[hb][ws]-ps[hs][wb]+ps[hs][ws]);
    }
  }
}