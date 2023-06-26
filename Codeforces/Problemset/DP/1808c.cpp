#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=20;
const I MAX=1e9;
vector<I>lows,upps;
vector<I>ress;
pair<I,tuple<I,I,I>>dp[N+1][10][1<<2];
void cmb(pair<I,tuple<I,I,I>>&a,pair<I,tuple<I,I,I>>b){
  a=min(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    Lli l,r;cin>>l>>r;
    lows.clear(),upps.clear();
    for(Lli t=l;t;t/=10)lows.push_back(t%10);
    for(Lli t=r;t;t/=10)upps.push_back(t%10);
    I n=upps.size();
    if(lows.size()<n){
      Lli res=1,opt=1;
      for(I i=0;i<n-1;i++)res*=10;
      for(I i=0;i<n-2;i++)opt*=10,opt+=1;
      if(res+opt<=r)res+=opt;
      for(I i=1;i<=9;i++)if(i*opt>=l&&i*opt<=r)res=i*opt;
      printf("%lli\n",res);
      continue;
    }
    reverse(lows.begin(),lows.end());
    reverse(upps.begin(),upps.end());
    fill(&dp[0][0][0],&dp[0][0][0]+(N+1)*10*(1<<2),pair<I,tuple<I,I,I>>{MAX,{-1,-1,-1}});
    I low=lows[0],upp=upps[0];
    for(I i=low;i<=upp;i++)dp[1][i][(i==low)<<1|(i==upp)]={i,{i,-1,-1}};
    for(I i=1;i<n;i++)for(I j=0;j<10;j++){
      I low=lows[i],upp=upps[i];
      for(I l=0;l<=9;l++)cmb(dp[i+1][min(j,l)][0&((l==low)<<1|(l==upp))],{max(dp[i][j][0].first,l),{l,j,0}});
      for(I l=0;l<=upp;l++)cmb(dp[i+1][min(j,l)][1&((l==low)<<1|(l==upp))],{max(dp[i][j][1].first,l),{l,j,1}});
      for(I l=low;l<=9;l++)cmb(dp[i+1][min(j,l)][2&((l==low)<<1|(l==upp))],{max(dp[i][j][2].first,l),{l,j,2}});
      for(I l=low;l<=upp;l++)cmb(dp[i+1][min(j,l)][3&((l==low)<<1|(l==upp))],{max(dp[i][j][3].first,l),{l,j,3}});
    }
    pair<I,pair<I,I>>res={MAX,{-1,-1}};
    for(I i=0;i<10;i++)for(I j=0;j<(1<<2);j++)res=min(res,{dp[n][i][j].first-i,{i,j}});
    auto[dis,pos]=res;auto[a,b]=pos;
    ress.clear();
    for(I i=n;i>=1;i--){
      auto[dis,pos]=dp[i][a][b];auto[j,c,d]=pos;
      ress.push_back(j);
      a=c,b=d;
    }
    while(ress.back()==0)ress.pop_back();
    reverse(ress.begin(),ress.end());
    for(auto i:ress)printf("%i",i);
    printf("\n");
  }
}