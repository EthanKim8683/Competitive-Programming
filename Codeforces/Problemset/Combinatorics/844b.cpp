#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=50;
const I M=50;
I cnts1[N][2],cnts2[M][2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++){
    I col;cin>>col;
    cnts1[i][col]++;
    cnts2[j][col]++;
  }
  Lli res=0;
  for(I i=0;i<n;i++)for(I j=0;j<2;j++)res+=(1ll<<cnts1[i][j])-1;
  for(I i=0;i<m;i++)for(I j=0;j<2;j++)res+=(1ll<<cnts2[i][j])-1;
  res-=n*m;
  printf("%lli\n",res);
}
/*
by the second condition, all selected sets must be in either the same row or
column
*/