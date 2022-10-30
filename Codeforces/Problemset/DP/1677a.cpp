#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=5000;

I p_arr[N];
Lli ps[N+1][N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<=n;i++)for(I j=0;j<=n;j++)ps[i][j]=0;
    for(I i=0;i<n;i++)cin>>p_arr[i];
    for(I i=0;i<n;i++)ps[i+1][p_arr[i]]++;
    for(I i=1;i<=n;i++)for(I j=1;j<=n;j++)ps[i][j]+=ps[i-1][j]+ps[i][j-1]-ps[i-1][j-1];
    Lli res=0;
    for(I i=0;i<n;i++)for(I j=i+1;j<n;j++){
      I a=p_arr[i]-1,b=p_arr[j]-1;
      Lli lft=ps[i][b]-ps[0][b]-ps[i][0]+ps[0][0];
      Lli rgt=ps[n][a]-ps[j+1][a]-ps[n][0]+ps[j+1][0];
      res+=lft*rgt;
    }
    printf("%lli\n",res);
  }
}