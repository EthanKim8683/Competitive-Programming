#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I Q=3e5;
const I LOGQ=19;
I cnts[Q+1],csts[Q+1];
I ancs[Q+1][LOGQ];
I deps[Q+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q,a,c;cin>>q>>a>>c;
  cnts[0]=a,csts[0]=c;
  for(I i=1;i<=q;i++){
    I t;cin>>t;
    if(t==1){
      I p,a,c;cin>>p>>a>>c;
      cnts[i]=a,csts[i]=c,deps[i]=deps[p]+1,ancs[i][0]=p;
      for(I j=1;j<LOGQ;j++)ancs[i][j]=ancs[ancs[i][j-1]][j-1];
    }
    if(t==2){
      I v,w;cin>>v>>w;
      I u=v;
      for(I j=LOGQ-1;j>=0;j--)if(cnts[ancs[u][j]]>0)u=ancs[u][j];
      Lli rem=w,cst=0;
      for(I j=deps[u];j<=deps[v]&&rem>0;j++){
        I x=v;
        for(I k=LOGQ-1;k>=0;k--)if(deps[ancs[x][k]]>=j)x=ancs[x][k];
        Lli dif=min(rem,(Lli)cnts[x]);
        cst+=dif*csts[x],rem-=dif,cnts[x]-=dif;
      }
      printf("%lli %lli\n",w-rem,cst),fflush(stdout);
    }
  }
}