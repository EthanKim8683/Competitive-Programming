#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;

const I N=20;
const I M=20;

I a_arr[N];
I b_arr[M];
I ps[N];
I dp[1<<M];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<m;i++)cin>>b_arr[i];
  sort(a_arr,a_arr+n);
  ps[0]=a_arr[0];
  for(I i=1;i<n;i++)
    ps[i]=ps[i-1]+a_arr[i];
  fill_n(dp,1<<m,-1);
  dp[0]=0;
  for(I i=0;i<(1<<m);i++){
    if(dp[i]!=-1){
      for(I j=0;j<m;j++){
        if(~i>>j&1){
          I sum=dp[i]+b_arr[j];
          if(upper_bound(ps,ps+n,dp[i])==lower_bound(ps,ps+n,sum)){
            if(sum==ps[n-1]){
              printf("YES\n");
              return 0;
            }
            dp[i|1<<j]=sum;
          }
        }
      }
    }
  }
  printf("NO\n");
  return 0;
}