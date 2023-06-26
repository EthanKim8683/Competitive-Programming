#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=50;
const I M=50;
const I C=100;
const I X=100;
const Lli MIN=-1e18;
pair<Lli,Lli>subs[M];
vector<I>coms[C+1];
map<Lli,tuple<Lli,I,I>>dp[C+1];
pair<I,I>pars[N+1][M][X+1];
vector<pair<I,Lli>>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  for(I i=0;i<m;i++){
    Lli a,b;I c;cin>>a>>b>>c;
    subs[i]={a,b};
    coms[c].push_back(i);
  }
  fill(&pars[0][0][0],&pars[0][0][0]+(N+1)*M*(X+1),pair<I,I>{-1,-1});
  for(I i=1;i<=C;i++){
    for(I y=i-1;y>=1;y--){
      for(auto j:coms[i]){
        auto[a,b]=subs[j];
        for(Lli x=a;x<=b;x++){
          if(dp[y].find(x-k)!=dp[y].end()){
            auto[tot,p1,p2]=dp[y][x-k];
            tuple<Lli,I,I>cur={tot+x,j,x-a};
            if(cur>dp[y+1][x])dp[y+1][x]=cur,pars[y+1][j][x-a]={p1,p2};
          }
          if(x%k==0&&dp[y].find(x/k)!=dp[y].end()){
            auto[tot,p1,p2]=dp[y][x/k];
            tuple<Lli,I,I>cur={tot+x,j,x-a};
            if(cur>dp[y+1][x])dp[y+1][x]=cur,pars[y+1][j][x-a]={p1,p2};
          }
        }
      }
    }
    for(auto j:coms[i]){
      auto[a,b]=subs[j];
      for(Lli x=a;x<=b;x++)dp[1][x]=max(dp[1][x],{x,j,x-a});
    }
  }
  tuple<Lli,I,I>res={MIN,-1,-1};
  for(auto[x,y]:dp[n])res=max(res,y);
  auto[tot,p1,p2]=res;
  if(tot==MIN)printf("NO\n"),exit(0);
  for(I i=n;i>=1;i--){
    auto[a,b]=subs[p1];
    ress.push_back({p1,p2+a});
    tie(p1,p2)=pars[i][p1][p2];
  }
  reverse(ress.begin(),ress.end());
  printf("YES\n");
  for(auto[x,y]:ress)printf("%i %lli\n",x+1,y);
}