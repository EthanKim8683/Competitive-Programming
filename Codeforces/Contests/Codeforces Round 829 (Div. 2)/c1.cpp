#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=200000;
const I MIN=-1e9;

I a_arr[N];
vector<I>rems;
I dp[N+1][2];
I pars[N+1][2];
vector<I>movs;
vector<pair<I,I>>ress;
B viss[N];

void cmb(I i,I j,I k){
  if(dp[i][j]+k<=dp[i+1][k])return;
  dp[i+1][k]=dp[i][j]+k,pars[i+1][k]=j;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I sum=accumulate(a_arr,a_arr+n,0);
    if(sum%2){printf("-1\n");continue;}
    rems.clear();
    for(I i=0;i<n;i++)if(i>0&&sum*a_arr[i]>0)rems.push_back(i);
    I k=rems.size();
    for(I i=0;i<=k;i++)dp[i][0]=dp[i][1]=0;
    I pre=MIN;
    for(I i=0;i<k;i++){
      I j=rems[i];
      if(j-pre==1){
        cmb(i,0,1);
        cmb(i,1,0);
        cmb(i,0,0);
      }else{
        cmb(i,1,1);
        cmb(i,0,1);
        cmb(i,1,0);
        cmb(i,0,0);
      }
      pre=j;
    }
    I j=dp[k][1]>dp[k][0];
    if(2*dp[k][j]<abs(sum)){printf("-1\n");continue;}
    movs.clear();
    ress.clear();
    for(I i=k;i>0;i--){
      if(j==1)movs.push_back(rems[i-1]);
      j=pars[i][j];
    }
    fill_n(viss,n,0);
    for(I i=0;2*i<abs(sum);i++){
      I j=movs[i];
      ress.push_back({j-1,j});
      viss[j-1]=viss[j]=1;
    }
    for(I i=0;i<n;i++)if(!viss[i])ress.push_back({i,i});
    sort(ress.begin(),ress.end());
    printf("%i\n",ress.size());
    for(auto[l,r]:ress)printf("%i %i\n",l+1,r+1);
  }
}