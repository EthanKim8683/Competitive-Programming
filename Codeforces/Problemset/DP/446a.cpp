#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;
const I MIN=-1e9;
const I MAX=1e9;

I a_arr[N];
I dp1[N],dp2[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(dp1,n,1),fill_n(dp2,n,1);
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i+1<n;i++)if(a_arr[i+1]>a_arr[i])dp1[i+1]=dp1[i]+1;
  for(I i=n-1;i>0;i--)if(a_arr[i-1]<a_arr[i])dp2[i-1]=dp2[i]+1;
  I res=1;
  for(I i=0;i<n;i++){
    I a1=MIN,a2=MAX,len1=0,len2=0;
    if(i-1>=0)a1=a_arr[i-1],len1=dp1[i-1];
    if(i+1<n)a2=a_arr[i+1],len2=dp2[i+1];
    res=max(res,len1+1);
    res=max(res,len2+1);
    if(a1+1<=a2-1)res=max(res,len1+len2+1);
  }
  printf("%i\n",res);
}