#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
using B=bool;
const I N=700;
const Lli MOD=1e9+7;
vector<I>stks;
vector<I>adjs[N+1];
Lli dp1[N][3][3];
Lli dp2[N][3][3];
void dfs(I a){
  I n=adjs[a].size();
  if(n==0){dp1[a][0][1]=dp1[a][1][0]=dp1[a][0][2]=dp1[a][2][0]=1;return;}
  for(auto b:adjs[a])dfs(b);
  for(I i=0;i<n;i++)for(I j=0;j<3;j++)for(I k=0;k<3;k++)dp2[i][j][k]=0;
  for(I i=1;i<3;i++)dp2[0][i][0]=dp1[adjs[a][0]][i][0],dp2[0][0][i]=dp1[adjs[a][0]][0][i];
  for(I i=1;i<n;i++)for(I j=0;j<3;j++)for(I k=0;k<3;k++){
    (dp2[i][j][k]+=dp2[i-1][j][0]*dp1[adjs[a][i]][0][k])%=MOD;
    (dp2[i][j][k]+=dp2[i-1][j][0]*dp1[adjs[a][i]][1][k])%=MOD;
    (dp2[i][j][k]+=dp2[i-1][j][0]*dp1[adjs[a][i]][2][k])%=MOD;
    (dp2[i][j][k]+=dp2[i-1][j][1]*dp1[adjs[a][i]][0][k])%=MOD;
    (dp2[i][j][k]+=dp2[i-1][j][1]*dp1[adjs[a][i]][2][k])%=MOD;
    (dp2[i][j][k]+=dp2[i-1][j][2]*dp1[adjs[a][i]][0][k])%=MOD;
    (dp2[i][j][k]+=dp2[i-1][j][2]*dp1[adjs[a][i]][1][k])%=MOD;
  }
  for(I i=1;i<3;i++)for(I j=0;j<3;j++)for(I k=0;k<3;k++){
    if(i!=k)(dp1[a][0][i]+=dp2[n-1][j][k])%=MOD;
    if(i!=j)(dp1[a][i][0]+=dp2[n-1][j][k])%=MOD;
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n=s.size();
  stks.push_back(n);
  for(I i=0;i<n;i++){
    if(s[i]=='(')adjs[stks.back()].push_back(i),stks.push_back(i);
    if(s[i]==')')stks.pop_back();
  }
  dfs(n);
  I m=adjs[n].size();
  Lli res=0;
  for(I i=0;i<3;i++)for(I j=0;j<3;j++)(res+=dp2[m-1][i][j])%=MOD;
  printf("%lli\n",res);
}