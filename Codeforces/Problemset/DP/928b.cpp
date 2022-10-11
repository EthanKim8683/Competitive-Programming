#include<bits/stdc++.h>

using namespace std;

using I=int;
struct Dp{I tot,l,r;};

const I N=1e5;

I a_arr[N];
Dp dp[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++){I a;cin>>a,a_arr[i]=a-1;}
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    dp[i].l=max(i-k,0);
    dp[i].r=min(i+k,n-1);
    if(a!=-1){
      Dp pre=dp[a];
      dp[i].tot+=pre.tot;
      if(pre.r>=dp[i].l)dp[i].l=pre.l;
      else dp[i].tot+=pre.r-pre.l+1;
    }
  }
  for(I i=0;i<n;i++)dp[i].tot+=dp[i].r-dp[i].l+1;
  for(I i=0;i<n;i++)printf("%i ",dp[i].tot);
}