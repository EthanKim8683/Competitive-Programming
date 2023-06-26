#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
I a_arr[N-1];
Lli ps[2][N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++)cin>>a_arr[i];
  for(I i=0;i<2;i++)for(I j=0;j<n-1;j++){
    I a=(a_arr[j]-i)/2*2+i;
    ps[i][j+1]=a?ps[i][j]+a:0;
  }
  Lli pre1=0,pre2=0,res=0;
  for(I i=0;i<n;i++){
    pre1=max(pre1,ps[0][i]-ps[1][i]);
    pre2=max(pre2,ps[1][i]-ps[0][i]+pre1);
    res=max(res,ps[0][i]+pre2);
  }
  printf("%lli\n",res);
}