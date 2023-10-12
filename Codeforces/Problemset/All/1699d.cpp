#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=5000;
const I MIN=-1e9;
I a_arr[N];
I cnts[N];
I dp[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    fill_n(dp,n,MIN);
    I upp=0;
    fill_n(cnts,n,0);
    for(I i=0;i<n;i++){
      if(i%2==0&&i/2>=upp)dp[i]=max(dp[i],1);
      upp=max(upp,++cnts[a_arr[i]-1]);
    }
    for(I i=0;i<n;i++){
      I upp=0;
      fill_n(cnts,n,0);
      for(I j=i+1;j<n;j++){
        if((j-i-1)%2==0&&(j-i-1)/2>=upp&&a_arr[i]==a_arr[j])dp[j]=max(dp[j],dp[i]+1);
        upp=max(upp,++cnts[a_arr[j]-1]);
      }
    }
    I res=0;
    upp=0;
    fill_n(cnts,n,0);
    for(I i=n-1;i>=0;i--){
      if((n-i-1)%2==0&&(n-i-1)/2>=upp)res=max(res,dp[i]);
      upp=max(upp,++cnts[a_arr[i]-1]);
    }
    printf("%i\n",res);
  }
}
/*
a subarray is not removable if it is of odd length or if more than half of
all elements in the subarray are equal

if the above condition is satisfied, a subarray is always removable since
each element, if not equal to the last remaining element, can be paired and
otherwise stored for future elements

we can use dynamic programming validating transitions using the above
property to find the maximum number of equal elements remaining after
subarray removals
*/