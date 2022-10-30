#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=2000;
const I H=2000;
const I MIN=-1e9;

I a_arr[N];
I dp[N+1][H];
I l,r;

void cmb(I&a,I b){
  a=max(a,b);
}

B chk(I x){
  return x>=l&&x<=r;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,h;cin>>n>>h>>l>>r;
  fill(&dp[0][0],&dp[0][0]+(N+1)*H,MIN);
  for(I i=0;i<n;i++)cin>>a_arr[i];
  dp[0][0]=0;
  for(I i=0;i<n;i++)for(I j=0;j<h;j++){
    I a=a_arr[i];
    I k1=(j+a)%h,k2=(j+a-1)%h;
    cmb(dp[i+1][k1],dp[i][j]+chk(k1));
    cmb(dp[i+1][k2],dp[i][j]+chk(k2));
  }
  printf("%i\n",*max_element(dp[n],dp[n]+h));
}