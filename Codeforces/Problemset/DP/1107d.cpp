#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using B=bool;
const I N=5200;
C cels[N][N/4+1];
I ps[N+1][N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>cels[i];
  for(I i=0;i<n;i++)for(I j=0;j<n/4;j++){
    C c=cels[i][j];
    I d;
    if(c>='A'&&c<='F')d=c-'A'+10;
    if(c>='0'&&c<='9')d=c-'0';
    ps[i+1][j*4+1]=d>>3&1;
    ps[i+1][j*4+2]=d>>2&1;
    ps[i+1][j*4+3]=d>>1&1;
    ps[i+1][j*4+4]=d>>0&1;
  }
  for(I i=1;i<=n;i++)for(I j=1;j<=n;j++)
    ps[i][j]+=ps[i-1][j]+ps[i][j-1]-ps[i-1][j-1];
  I res=1;
  for(I i=2;i<=n;i++){
    if(n%i)continue;
    B vld=1;
    for(I j=0;j<n;j+=i)for(I k=0;k<n;k+=i){
      I sum=ps[j+i][k+i]-ps[j][k+i]-ps[j+i][k]+ps[j][k];
      vld&=sum==i*i||sum==0;
    }
    if(vld)res=max(res,i);
  }
  printf("%i\n",res);
}