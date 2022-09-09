#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=500;

I x_arr[N];
Lli adjs[N][N];
vector<I>viss;
Lli ress[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)cin>>adjs[i][j];
  for(I i=0;i<n;i++){I x;cin>>x,x_arr[i]=x-1;}
  for(I i=n-1;i>=0;i--){
    I x=x_arr[i];
    viss.push_back(x);
    Lli res=0;
    for(I j=0;j<n;j++)for(I k=0;k<n;k++)
      adjs[j][k]=min(adjs[j][k],adjs[j][x]+adjs[x][k]);
    for(auto j:viss)for(auto k:viss)res+=adjs[j][k];
    ress[i]=res;
  }
  for(I i=0;i<n;i++)printf("%lli ",ress[i]);
  return 0;
}