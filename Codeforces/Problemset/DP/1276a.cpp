#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using C=char;

const I N=1.5e5;
const I MAX=1e9;

C chrs[]="otnwex";
I dp[N][6][6];
I pars[N][6][6];
vector<I>ress;

I tod(C c){
  return find(chrs,chrs+5,c)-chrs;
}

C toc(I i){
  return chrs[i];
}

void add(I i,I j,I k,I l){
  if(dp[i-1][j][k]+1<dp[i][j][k]){
    dp[i][j][k]=dp[i-1][j][k]+1;
    pars[i][j][k]=-1;
  }
  if(toc(j)=='o'&&toc(k)=='n'&&toc(l)=='e')return;
  if(toc(j)=='t'&&toc(k)=='w'&&toc(l)=='o')return;
  if(dp[i-1][j][k]<dp[i][k][l]){
    dp[i][k][l]=dp[i-1][j][k];
    pars[i][k][l]=j;
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    I n=s.size();
    ress.clear();
    for(I i=0;i<n;i++)for(I j=0;j<6;j++)for(I k=0;k<6;k++)
      dp[i][j][k]=MAX;
    I c=tod(s[0]);
    dp[0][5][5]=1,pars[0][5][5]=-1;
    dp[0][5][c]=0,pars[0][5][c]=5;
    for(I i=1;i<n;i++)for(I j=0;j<6;j++)for(I k=0;k<6;k++)
      add(i,j,k,tod(s[i]));
    I res=MAX,l=-1,m=-1;
    for(I i=0;i<6;i++)for(I j=0;j<6;j++)if(dp[n-1][i][j]<res)
      res=dp[n-1][i][j],l=i,m=j;
    for(I i=n-1;i>=0;i--){
      I p=pars[i][l][m];
      if(p!=-1)m=l,l=p;
      else ress.push_back(i);
    }
    printf("%i\n",ress.size());
    for(auto i:ress)printf("%i ",i+1);
    printf("\n");
  }
}