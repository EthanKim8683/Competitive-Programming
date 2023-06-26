#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
const I MAX=N;
I a_arr[N];
I dp1[N],dp2[N],dp3[N],dp4[N],dp5[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,d;cin>>n>>d;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  copy_n(a_arr,n,dp1);
  for(I i=0;i+1<n;i++)dp1[i+1]+=dp1[i];
  copy_n(dp1,n,dp2);
  for(I i=n-1;i>0;i--)dp2[i-1]=max(dp2[i-1],dp2[i]);
  for(I i=0;i<n;i++)dp3[i]=d-dp2[i];
  for(I i=0;i<n;i++)if(a_arr[i]==0)dp4[i]=-dp1[i];
  for(I i=0;i+1<n;i++)dp4[i+1]=max(dp4[i+1],dp4[i]);
  if(*min_element(dp3,dp3+n)<0)printf("-1\n"),exit(0);
  fill_n(dp5,n,MAX);
  dp5[0]=0;
  I res=MAX;
  for(I i=0;i<n;i++){
    I j=upper_bound(dp4,dp4+n,dp3[i])-dp4;
    I k=upper_bound(dp4,dp4+n,dp4[i])-dp4;
    if(j==n)res=min(res,dp5[i]+1);
    if(k==n)res=min(res,dp5[i]);
    if(j-1>i)dp5[j-1]=min(dp5[j-1],dp5[i]+1);
    if(k-1>i)dp5[k-1]=min(dp5[k-1],dp5[i]);
  }
  printf("%i\n",res==MAX?-1:res);
}