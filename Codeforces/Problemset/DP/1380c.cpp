#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;

const I N=1e5;

I a_arr[N];
I dp[N+1];

void cmb(I&a,I b){
  a=max(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,x;cin>>n>>x;
    fill_n(dp,n+1,0);
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n);
    for(I i=0;i<n;i++){
      I a=a_arr[i];
      I b=x/a+!!(x%a);
      if(i+b<=n)cmb(dp[i+b],dp[i]+1);
      if(i+1<=n)cmb(dp[i+1],dp[i]);
    }
    printf("%i\n",dp[n]);
  }
  return 0;
}