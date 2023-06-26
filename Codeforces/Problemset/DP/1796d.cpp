#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const I K=20;
const Lli MAX=1e18;
const Lli MIN=-MAX;
I a_arr[N];
Lli pres[N+1][K+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k,x;cin>>n>>k>>x;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    fill_n(pres[0],k+1,0);
    Lli res=0,pre=0;
    for(I i=0;i<n;i++){
      pre+=a_arr[i]-x;
      for(I j=0;j<=min(k,i+1);j++)pres[i+1][j]=min(pres[i][j],pre+(Lli)j*2*x);
      for(I j=max(k-(n-(i+1)),0);j<=min(k,i+1);j++)for(I l=0;l<=j;l++)if(i+1>=j-l)res=max(res,pre+(Lli)j*2*x-pres[i+1-(j-l)][l]);
    }
    printf("%lli\n",res);
  }
}