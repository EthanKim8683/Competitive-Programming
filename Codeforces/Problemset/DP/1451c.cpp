#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=1e6;

B dp[26+1][N+1];
I cnts1[26],cnts2[26];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    fill_n(cnts1,26,0);
    fill_n(cnts2,26,0);
    I n,k;cin>>n>>k;
    for(I i=0;i<=26;i++)for(I j=0;j<=n;j++)dp[i][j]=0;
    S a;cin>>a;
    S b;cin>>b;
    for(auto c:a)cnts1[c-'a']++;
    for(auto c:b)cnts2[c-'a']++;
    dp[0][cnts1[0]]=1;
    for(I i=0;i<26;i++)for(I j=cnts1[i];j<=n;j+=k)
      dp[i+1][(i+1<26?cnts1[i+1]:0)+j-cnts2[i]]|=dp[i][j];
    printf("%s\n",dp[26][0]?"Yes":"No");
  }
}