#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;

const I N=100;

I a_arr[N];
I dp[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I sum=0;
    for(I i=0;i<n;i++)sum+=a_arr[i];
    if(sum%2){printf("NO\n");continue;}
    fill_n(dp,sum/2+1,0);
    dp[0]=1;
    for(I i=0;i<n;i++){
      I a=a_arr[i];
      for(I j=sum/2-a;j>=0;j--)dp[j+a]+=dp[j];
    }
    printf("%s\n",dp[sum/2]?"YES":"NO");
  }
  return 0;
}