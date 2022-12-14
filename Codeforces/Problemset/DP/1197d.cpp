#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=3e5;
const I M=10;
I a_arr[N];
Lli ps[N+1][M];
Lli pm[N+1][M];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)ps[i+1][j]=a_arr[i]-(i%m==j)*k+ps[i][j];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)pm[i+1][j]=min(ps[i+1][j],pm[i][j]);
  Lli res=0;
  for(I i=0;i<n;i++)res=max(res,ps[i+1][i%m]-pm[i][i%m]);
  printf("%lli\n",res);
}