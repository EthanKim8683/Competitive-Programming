#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=500;
const I K=N;
const I MAX=1e9;
I dp1[N+1][N+1];
pair<I,I>dp2[N+1][K+1];
vector<pair<I,I>>rngs;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp2[0][0],&dp2[0][0]+(N+1)*(K+1),pair<I,I>{MAX,-1});
  S s;cin>>s;
  I k;cin>>k;
  I n=s.size();
  for(I i=2;i<=n;i++)for(I j=0;j+i<=n;j++)dp1[j][j+i]=dp1[j+1][j+i-1]+(s[j]!=s[j+i-1]);
  dp2[0][0]={0,-1};
  for(I i=1;i<=n;i++)for(I j=i-1;j>=0;j--)for(I l=1;l<=k;l++)dp2[i][l]=min(dp2[i][l],{dp2[j][l-1].first+dp1[j][i],j});
  I j=min_element(dp2[n],dp2[n]+k+1)-dp2[n],i=n;
  I res=dp2[n][j].first;
  while(1){
    auto[tot,p]=dp2[i][j];
    if(p==-1)break;
    rngs.push_back({p,i});
    j--,i=p;
  }
  reverse(rngs.begin(),rngs.end());
  for(auto[l,r]:rngs)for(I i=l,j=r-1;i<j;i++,j--)if(s[i]!=s[j])s[j]=s[i];
  auto[l,r]=rngs[0];
  printf("%i\n",res);
  printf("%s",s.substr(l,r-l).c_str());
  for(I i=1;i<rngs.size();i++){
    auto[l,r]=rngs[i];
    printf("+%s",s.substr(l,r-l).c_str());
  }
}