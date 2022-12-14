#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using C=char;
const I M=100;
const I K=100;
const I MIN=-1e9;
I bons[26][26];
I dp[M][K+1][26];
void cmb(I&a,I b){
  a=max(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+M*(K+1)*26,MIN);
  S s;I k;cin>>s>>k;
  I n;cin>>n;
  for(I i=0;i<n;i++){
    C x,y;I c;cin>>x>>y>>c;
    bons[x-'a'][y-'a']=c;
  }
  I m=s.size();
  for(I i=0;i<m;i++)s[i]-='a';
  for(I i=0;i<26;i++)dp[0][s[0]!=i][i]=0;
  for(I i=0;i+1<m;i++)for(I j=0;j<=k;j++)for(I l=0;l<26;l++){
    for(I o=0;o<26;o++){
      I p=j+(o!=s[i+1]);
      if(p<=k)cmb(dp[i+1][p][o],dp[i][j][l]+bons[l][o]);
    }
  }
  I res=MIN;
  for(I i=0;i<=k;i++)for(I j=0;j<26;j++)cmb(res,dp[m-1][i][j]);
  printf("%i\n",res);
}