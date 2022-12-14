#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=3e5;
const Lli MIN=-1e18;
I a_arr[N];
I b_arr[N];
Lli ps1[3][N+1];
Lli ps2[3][N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cin>>b_arr[i];
  for(I i=0;i<n;i++){
    I j=n-i-1;
    Lli a=a_arr[i],b=b_arr[i];
    Lli c=a_arr[j],d=b_arr[j];
    ps1[0][j+1]=-c*(i+1);
    ps1[1][j+1]=c*i;
    ps1[2][i+1]=a;
    ps2[0][j+1]=-d*(i+1);
    ps2[1][j+1]=d*i;
    ps2[2][i+1]=b;
  }
  for(I i=0;i<3;i++)for(I j=0;j<n;j++){
    ps1[i][j+1]+=ps1[i][j];
    ps2[i][j+1]+=ps2[i][j];
  }
  Lli res=MIN,run=0;
  for(I i=0;i<=n;i++){
    Lli a=a_arr[i],b=b_arr[i];
    I j=i%2,k=!j;
    Lli fac=2*i+(n-i),cur=run;
    cur+=(ps1[2][n]-ps1[2][i])*fac+ps1[j][n]-ps1[j][i];
    cur+=(ps2[2][n]-ps2[2][i])*fac+ps2[k][n]-ps2[k][i];
    res=max(res,cur);
    run+=(2*i+j)*a;
    run+=(2*i+k)*b;
  }
  printf("%lli\n",res);
}