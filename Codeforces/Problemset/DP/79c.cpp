#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=10;
const I M=1e5;
const I K=N*M;
S b_arr[N];
vector<pair<I,I>>rngs;
I dp[K];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n;cin>>n;
  I m=s.size();
  for(I i=0;i<n;i++)cin>>b_arr[i];
  for(I i=0;i<m;i++){
    for(I j=0;j<n;j++){
      S b=b_arr[j];
      I k=b.size();
      if(i+k>m)continue;
      if(s.substr(i,k)!=b)continue;
      rngs.push_back({i+1,i+k-1});
    }
  }
  rngs.push_back({0,m});
  sort(rngs.begin(),rngs.end());
  I k=rngs.size();
  fill_n(dp,k,m);
  for(I i=0;i<k;i++){
    auto[low,upp]=rngs[i];
    if(i-1>=0)dp[i-1]=upp;
  }
  for(I i=k-1;i>0;i--)dp[i-1]=min(dp[i-1],dp[i]);
  pair<I,I>res={0,0};
  for(I i=0;i<k;i++){
    auto[low,upp]=rngs[i];
    res=max(res,{dp[i]-low,low});
  }
  auto[len,pos]=res;
  printf("%i %i\n",len,pos);
}