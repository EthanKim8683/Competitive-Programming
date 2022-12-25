#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=300;
const Lli MAX=1e18;
const Lli MIN=-1e18;
I r_arr[N][N];
Lli ress[N];
Lli tmps[N];
I main(){
  I n;cin>>n;
  for(I i=0;i<n;i++)for(I j=i;j<n;j++)cin>>r_arr[i][j];
  for(I i=n-1;i>0;i--){
    Lli dif=r_arr[i-1][i]-r_arr[i-1][i-1];
    B vld=0;
    for(I j=0;j<2&&!vld;j++)for(I k=0;k<2&&!vld;k++){
      for(I l=i;l<n;l++)tmps[l]=(2*j-1)*ress[l]+(2*k-1)*dif;
      Lli low=MAX,upp=MIN;
      vld=1;
      for(I l=i-1;l<n;l++){
        low=min(low,tmps[l]),upp=max(upp,tmps[l]);
        vld&=upp-low==r_arr[i-1][l];
      }
    }
    copy_n(tmps+i,n-i,ress+i);
  }
  Lli low=-1e9-*min_element(ress,ress+n);
  for(I i=0;i<n;i++){
    printf("%lli",ress[i]+low);
    if(i+1<n)printf(" ");
  }
  printf("\n");
}