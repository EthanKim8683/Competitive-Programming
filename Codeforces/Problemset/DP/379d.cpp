#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I K=50;
const I N=100;
const I M=100;
Lli fibs1[K+1],fibs2[K+1],fibs3[K+1],fibs4[K+1],fibs5[K+1];
tuple<B,I,I>dp[N+1][N/2+1][3][3];
vector<I>ress1,ress2;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0][0],&dp[0][0][0][0]+(N+1)*(N/2+1)*3*3,tuple<B,I,I>{0,-1,-1});
  I k,x,n,m;cin>>k>>x>>n>>m;
  fibs2[2]=fibs2[3]=1;
  for(I i=4;i<=k;i++)fibs2[i]=fibs2[i-1]+fibs2[i-2];
  fibs1[3]=fibs1[4]=1;
  for(I i=5;i<=k;i++)fibs1[i]=fibs1[i-1]+fibs1[i-2];
  fibs4[3]=fibs4[4]=1;
  for(I i=5;i<=k;i++)fibs4[i]=fibs4[i-1]+fibs4[i-2];
  fibs5[4]=fibs5[5]=1;
  for(I i=6;i<=k;i++)fibs5[i]=fibs5[i-1]+fibs5[i-2]+1-i%2;
  fibs3[5]=fibs3[6]=1;
  for(I i=7;i<=k;i++)fibs3[i]=fibs3[i-1]+fibs3[i-2]+i%2;
  dp[1][0][0][0]=dp[1][0][1][1]=dp[1][0][2][2]={1,-1,-1};
  for(I i=1;i<max(n,m);i++)for(I j=0;j<=max(n,m)/2;j++)for(I l=0;l<3;l++){
    if(get<0>(dp[i][j][l][0])){
      dp[i+1][j][l][0]={1,j,0};
      dp[i+1][j+1][l][1]={1,j,0};
      dp[i+1][j][l][2]={1,j,0};
    }
    if(get<0>(dp[i][j][l][1])){
      dp[i+1][j][l][0]={1,j,1};
      dp[i+1][j][l][1]={1,j,1};
      dp[i+1][j][l][2]={1,j,1};
    }
    if(get<0>(dp[i][j][l][2])){
      dp[i+1][j][l][0]={1,j,2};
      dp[i+1][j][l][1]={1,j,2};
      dp[i+1][j][l][2]={1,j,2};
    }
  }
  for(I a=0;a<=2;a++)for(I b=0;b<=2;b++)for(I c=0;c<=2;c++)for(I d=0;d<=2;d++)for(I e=0;e<=n/2;e++)for(I f=0;f<=m/2;f++){
    if(!get<0>(dp[n][e][a][b])||!get<0>(dp[m][f][c][d]))continue;
    Lli cur=0;
    cur+=e*fibs1[k];
    cur+=f*fibs2[k];
    cur+=(d==0)*(c==1)*fibs3[k];
    cur+=(b==0)*(c==1)*fibs4[k];
    cur+=(d==0)*(a==1)*fibs5[k];
    if(cur!=x)continue;
    I j1=e,l1=b;
    for(I i=n;i>=1;i--){
      auto[vld,j2,l2]=dp[i][j1][a][l1];
      ress1.push_back(l1);
      tie(j1,l1)=tie(j2,l2);
    }
    j1=f,l1=d;
    for(I i=m;i>=1;i--){
      auto[vld,j2,l2]=dp[i][j1][c][l1];
      ress2.push_back(l1);
      tie(j1,l1)=tie(j2,l2);
    }
    reverse(ress1.begin(),ress1.end());
    reverse(ress2.begin(),ress2.end());
    for(auto i:ress1)printf("%c","ACB"[i]);
    printf("\n");
    for(auto i:ress2)printf("%c","ACB"[i]);
    printf("\n");
    exit(0);
  }
  printf("Happy new year!");
}