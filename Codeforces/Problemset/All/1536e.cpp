#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using Lli=long long int;
const I N=2000;
const I M=2000;
const Lli MOD=1e9+7;
C fors[N+1][M+1];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>fors[i];
    I cnt=0;
    for(I i=0;i<n;i++)for(I j=0;j<m;j++)cnt+=fors[i][j]=='#';
    Lli res=mpw(2,cnt);
    if(cnt==n*m)(res+=-1+MOD)%=MOD;
    printf("%lli\n",res);
  }
}
/*
for any non-0 cell in the forest, the value is already pre-determined to be
the result of a breadth-first search from every 0 cell, or, the minimum
Manhattan distance to a 0 cell

this means that configurations are dependent on the placement of 0's

if a configuration doesn't have any 0's it is invalid because at least one
non-0 cell will be the minimum and isn't strictly greater than any of its
adjacent cells
*/