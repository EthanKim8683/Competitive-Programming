#include<bits/stdc++.h>
 
using namespace std;
 
using I=int;
using B=bool;
 
const I L=30;
 
B dp[L+1][L];
 
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    I u,v;cin>>u>>v;
    if(v<u){printf("NO\n");continue;}
    fill(&dp[0][0],&dp[0][0]+(L+1)*L,0);
    dp[0][0]=1;
    for(I i=0;i<L;i++)for(I j=0;j<L;j++){
      I a=u>>i&1,b=v>>i&1;
      for(I k=0;j+a+k<L;k++)if(j+a>=k&&(j+a+k)%2==b)dp[i+1][(j+a+k)/2]|=dp[i][j];
    }
    printf("%s\n",dp[L][0]?"YES":"NO");
  }
}