#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100000;
const I M=10;
I a_arr[M][N];
I adjs[N];
I inds[N];
I dfs(I a){
  I b=adjs[a];
  if(b==-1)return 1;
  return dfs(b)+1;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++)for(I j=0;j<n;j++)cin>>a_arr[i][j];
  for(I i=0;i+1<n;i++)adjs[a_arr[0][i]-1]=a_arr[0][i+1]-1;
  adjs[a_arr[0][n-1]-1]=-1;
  for(I i=1;i<m;i++){
    for(I j=0;j+1<n;j++){
      I a=a_arr[i][j]-1,b=a_arr[i][j+1]-1;
      if(b!=adjs[a])adjs[a]=-1;
    }
    adjs[a_arr[i][n-1]-1]=-1;
  }
  for(I i=0;i<n;i++){
    I j=adjs[i];
    if(j==-1)continue;
    inds[j]++;
  }
  Lli res=0;
  for(I i=0;i<n;i++){
    if(inds[i])continue;
    Lli cnt=dfs(i);
    res+=cnt*(cnt+1)/2;
  }
  printf("%lli\n",res);
}