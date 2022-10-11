#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=50;
const I MIN=-1e9;

I a_arr[N];
pair<I,I>dp[N+1][2];
I ps[N+1];

void cmb1(pair<I,I>&a,pair<I,I>b){
  if(get<0>(b)>get<0>(a))a=b;
}

void cmb2(pair<I,I>&a,pair<I,I>b){
  if(get<1>(b)>get<1>(a))a=b;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+N*2,pair<I,I>{MIN,MIN});
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)ps[i+1]=a_arr[i];
  for(I i=0;i<n;i++)ps[i+1]+=ps[i];
  dp[n][0]=dp[n][1]={0,0};
  for(I i=n-1;i>=0;i--){
    for(I j=i+1;j<=n;j++){
      cmb1(dp[i][0],{get<0>(dp[j][1])+a_arr[j-1],get<1>(dp[j][1])+ps[j-1]-ps[i]});
      cmb2(dp[i][1],{get<0>(dp[j][0])+ps[j-1]-ps[i],get<1>(dp[j][0])+a_arr[j-1]});
    }
  }
  printf("%i %i\n",get<0>(dp[0][1]),get<1>(dp[0][1]));
}