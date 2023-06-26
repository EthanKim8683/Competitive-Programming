#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using B=bool;
const I N=50;
const I MIN=-1e9;
const I MAX=1e9;
I r_arr[N];
C c_arr[N];
I inds[N];
I dp[N][N*N+1];
B cmp(I a,I b){
  return r_arr[a]<r_arr[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+N*(N*N+1),MIN);
  I n,s,k;cin>>n>>s>>k,s--;
  for(I i=0;i<n;i++)cin>>r_arr[i];
  cin>>c_arr;
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  I res=MAX;
  for(I i=0;i<n;i++){
    I j=inds[i];
    dp[j][abs(s-j)]=max(dp[j][abs(s-j)],r_arr[j]);
    for(I t=0;t<=n*n;t++){
      for(I l=0;l<n;l++)if(r_arr[j]<r_arr[l]&&c_arr[j]!=c_arr[l])dp[l][t+abs(j-l)]=max(dp[l][t+abs(j-l)],dp[j][t]+r_arr[l]);
      if(dp[j][t]>=k)res=min(res,t);
    }
  }
  printf("%i\n",res==MAX?-1:res);
}