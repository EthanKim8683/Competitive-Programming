#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=30000;

Lli a_arr[N];
Lli dp1[N],dp2[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    fill_n(dp1,n,0);
    fill_n(dp2,n,0);
    for(I i=0;i+1<n;i++){
      I a=a_arr[i+0],b=a_arr[i+1];
      if(a<b)dp1[i+1]=b-a;
      if(a>b)dp2[i+0]=a-b;
    }
    for(I i=0;i+1<n;i++)dp1[i+1]+=dp1[i];
    for(I i=n-1;i>0;i--)dp2[i-1]+=dp2[i];
    for(I i=0;i<n;i++)a_arr[i]-=dp1[i]+dp2[i];
    printf("%s\n",*min_element(a_arr,a_arr+n)<0?"NO":"YES");
  }
}