#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using S=string;
const I N=100;
const I M=100;
const I K=10;
const I MIN=-1e9;
C brds[N][M+1];
pair<I,C>dp[N][M][K+1];
vector<C>movs;
void cmb(pair<I,C>&a,pair<I,C>b){
  a=max(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+N*M*(K+1),pair<I,C>{MIN,-1});
  I n,m,k;cin>>n>>m>>k,k++;
  for(I i=0;i<n;i++)cin>>brds[i];
  for(I i=0;i<m;i++){
    I pea=brds[n-1][i]-'0';
    dp[0][i][pea%k]={pea,-1};
  }
  for(I i=1;i<n;i++)for(I j=0;j<m;j++){
    I pea=brds[n-1-i][j]-'0';
    for(I l=0;l<k;l++){
      if(j-1>=0){
        auto[tot,mov]=dp[i-1][j-1][l];
        if(tot!=MIN)cmb(dp[i][j][(l+pea)%k],{tot+pea,'R'});
      }
      if(j+1<m){
        auto[tot,mov]=dp[i-1][j+1][l];
        if(tot!=MIN)cmb(dp[i][j][(l+pea)%k],{tot+pea,'L'});
      }
    }
  }
  pair<I,I>res={0,-1};
  for(I i=0;i<m;i++)res=max(res,{get<0>(dp[n-1][i][0]),i});
  auto[tot,j]=res;I l=0;
  if(j==-1)printf("-1\n"),exit(0);
  for(I i=n-1;i>0;i--){
    auto[tot,mov]=dp[i][j][l];
    (l-=brds[n-1-i][j]-'0')%=k,(l+=k)%=k,j+=(mov=='L')-(mov=='R');
    movs.push_back(mov);
  }
  reverse(movs.begin(),movs.end());
  printf("%i\n",tot);
  printf("%i\n",j+1);
  for(auto mov:movs)printf("%c",mov);
}