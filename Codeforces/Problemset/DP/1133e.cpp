#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=5000;
const I K=5000;
I a_arr[N];
I dp1[K+1];
I dp2[2][K+1][5+1];
void cmb(I&a,I b){
  a=max(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sort(a_arr,a_arr+n);
  I res=0;
  dp2[0][1][0]=1;
  for(I i=0;i<n;i++){
    for(I j=0;j<=k;j++){
      for(I l=0;l<=5;l++){
        res=max(res,dp2[i%2][j][l]);
        cmb(dp1[j],dp2[i%2][j][l]);
        if(i+1>=n)continue;
        if(dp2[i%2][j][l]==0)continue;
        I m=l+a_arr[i+1]-a_arr[i];
        if(m<=5)cmb(dp2[(i+1)%2][j][m],dp2[i%2][j][l]+1);
      }
      if(j+1<=k)cmb(dp2[(i+1)%2][j+1][0],dp1[j]+1);
    }
    for(I j=0;j<=k;j++)for(I l=0;l<=5;l++)dp2[i%2][j][l]=0;
  }
  printf("%i\n",res);
}