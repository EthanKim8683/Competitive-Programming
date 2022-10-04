#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=500;

B dp[N][2*N-1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    S s;cin>>s;
    S t;cin>>t;
    I n=s.size(),m=t.size();
    for(I i=0;i<=n;i++)for(I j=0;j<=m;j++)dp[i][j]=0;
    for(I i=0;i<n;i++)if(s[i]==t[0])dp[i][0]=1;
    for(I i=0;i+1<n;i++)for(I j=0;j+1<m;j++)
      if(s[i+1]==t[j+1])dp[i+1][j+1]|=dp[i][j];
    for(I i=n-1;i>0;i--)for(I j=0;j+1<m;j++)
      if(s[i-1]==t[j+1])dp[i-1][j+1]|=dp[i][j];
    B res=0;
    for(I i=0;i<n;i++)res|=dp[i][m-1];
    printf("%s\n",res?"YES":"NO");
  }
}