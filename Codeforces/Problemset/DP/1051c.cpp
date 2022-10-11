#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=100;
const I S=100;

I s_arr[N];
I cnts[S];
B dp[S+1][N][N];
pair<I,I>movs[S+1][N][N];
pair<I,I>rems[S];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){I s;cin>>s,s_arr[i]=s-1;}
  for(I i=0;i<n;i++)cnts[s_arr[i]]++;
  dp[0][0][0]=1;
  for(I i=0;i<S;i++){
    I cnt=cnts[i];
    for(I j=0;j<n;j++)for(I k=0;k<n;k++){
      if(!dp[i][j][k])continue;
      dp[i+1][j][k+(cnt==1)]=1;
      movs[i+1][j][k+(cnt==1)]={0,cnt};
      dp[i+1][j+(cnt==1)][k]=1;
      movs[i+1][j+(cnt==1)][k]={cnt,0};
      if(cnt>=1){
        dp[i+1][j+1][k+(cnt-1==1)]=1;
        movs[i+1][j+1][k+(cnt-1==1)]={1,cnt-1};
        dp[i+1][j+(cnt-1==1)][k+1]=1;
        movs[i+1][j+(cnt-1==1)][k+1]={cnt-1,1};
      }
    }
  }
  I res=-1;
  for(I i=0;i<n;i++)if(dp[S][i][i])res=i;
  if(res==-1)printf("NO\n"),exit(0);
  I j=res,k=res;
  for(I i=S;i>0;i--){
    auto[a,b]=movs[i][j][k];
    rems[i-1]={a,b};
    j-=a==1,k-=b==1;
  }
  printf("YES\n");
  for(I i=0;i<n;i++){
    I s=s_arr[i];
    auto&[a,b]=rems[s];
    if(a>0)printf("A"),a--;
    else if(b>0)printf("B"),b--;
  }
}