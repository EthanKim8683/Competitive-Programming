#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=50000;
const I K=5;
const I LOGN=16;
const I MAX=1e9;
vector<I>adjs[N];
pair<I,I>ancs[N][LOGN][K];
pair<I,I>tmps[2][K];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&ancs[0][0][0],&ancs[0][0][0]+N*LOGN*K,pair<I,I>{MAX,-1});
  I k,n,m,o;cin>>k>>n>>m>>o;
  for(I i=0;i<m;i++){
    I a,b,t;cin>>a>>b>>t;
    ancs[a][0][b%k]={t,b};
  }
  for(I i=1;i<LOGN;i++)for(I j=0;j<n;j++){
    for(I x=0;x<k;x++){
      auto[d1,a]=ancs[j][i-1][x];
      if(a==-1)continue;
      for(I y=0;y<k;y++){
        auto[d2,b]=ancs[a][i-1][y];
        if(b==-1)continue;
        ancs[j][i][y]=min(ancs[j][i][y],{d1+d2,b});
      }
    }
  }
  while(o--){
    I a,b;cin>>a>>b;
    I cnt=b/k-a/k,t=0;
    fill_n(tmps[t],k,pair<I,I>{MAX,-1});
    tmps[t][a%k]={0,a};
    for(I i=0;i<LOGN;i++)if(cnt>>i&1){
      fill_n(tmps[!t],k,pair<I,I>{MAX,-1});
      for(I x=0;x<k;x++){
        auto[d1,a]=tmps[t][x];
        if(a==-1)continue;
        for(I y=0;y<k;y++){
          auto[d2,b]=ancs[a][i][y];
          if(b==-1)continue;
          tmps[!t][y]=min(tmps[!t][y],{d1+d2,b});
        }
      }
      t=!t;
    }
    auto[d,c]=tmps[t][b%k];
    printf("%i\n",c==-1?-1:d);
  }
}