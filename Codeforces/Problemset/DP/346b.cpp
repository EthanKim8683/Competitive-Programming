#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using C=char;
const I N=100;
const I M=100;
const I K=100;
const I MIN=-1e9;
tuple<I,I,I,I>dp[N+1][M+1][K];
I jmps[K][26];
I pres[2*K+1];
vector<C>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+(N+1)*(M+1)*K,tuple<I,I,I,I>{MIN,-1,-1,-1});
  S s1;cin>>s1;
  S s2;cin>>s2;
  S vir;cin>>vir;
  I n=s1.size(),m=s2.size(),k=vir.size();
  for(I i=0;i<k;i++)for(I j=0;j<26;j++){
    S tmp=vir+"."+vir.substr(0,i)+S(1,j+'A');
    for(I l=1;l<tmp.size();l++){
      I p=pres[l-1];
      while(p>0&&tmp[l]!=tmp[p])p=pres[p-1];
      if(tmp[l]==tmp[p])p++;
      pres[l]=p;
    }
    jmps[i][j]=pres[tmp.size()-1];
  }
  dp[0][0][0]={0,-1,-1,-1};
  for(I i=0;i<=n;i++)for(I j=0;j<=m;j++)for(I l=0;l<k;l++){
    if(i<n&&j<m){
      C x=s1[i],y=s2[j],z=vir[l];
      if(x==y){
        I p=jmps[l][x-'A'];
        if(p<k)dp[i+1][j+1][p]=max(dp[i+1][j+1][p],{get<0>(dp[i][j][l])+1,i,j,l});
      }
    }
    if(i+1<=n)dp[i+1][j][l]=max(dp[i+1][j][l],{get<0>(dp[i][j][l]),i,j,l});
    if(j+1<=m)dp[i][j+1][l]=max(dp[i][j+1][l],{get<0>(dp[i][j][l]),i,j,l});
  }
  pair<I,I>res={0,-1};
  for(I i=0;i<k;i++)res=max(res,{get<0>(dp[n][m][i]),i});
  auto[len,l1]=res;
  if(len==0)printf("0"),exit(0);
  I i1=n,j1=m;
  while(1){
    auto[cur,i2,j2,l2]=dp[i1][j1][l1];
    if(l2==-1)break;
    if(i1!=i2&&j1!=j2)ress.push_back(s1[i2]);
    tie(i1,j1,l1)=tie(i2,j2,l2);
  }
  reverse(ress.begin(),ress.end());
  for(auto c:ress)printf("%c",c);
}