#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I M=1e3;
tuple<I,I,I>rngs1[100];
tuple<I,I,I>rngs2[1000];
I dp[M+1];
vector<tuple<I,I,I>>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    fill_n(rngs1,100,tuple<I,I,I>{-1,-1,-1});
    fill_n(rngs2,1000,tuple<I,I,I>{-1,-1,-1});
    for(I i=0;i<n;i++){
      S num;cin>>num;
      for(auto&c:num)c-='0';
      for(I j=0;j+2<=m;j++)rngs1[num[j]*10+num[j+1]]={j,j+1,i};
      for(I j=0;j+3<=m;j++)rngs2[num[j]*100+num[j+1]*10+num[j+2]]={j,j+2,i};
    }
    S s;cin>>s;
    fill_n(dp,m+1,-1);
    dp[0]=0;
    for(auto&c:s)c-='0';
    for(I i=0;i<m;i++)if(dp[i]!=-1){
      if(i+2<=m&&get<2>(rngs1[s[i]*10+s[i+1]])!=-1)dp[i+2]=i;
      if(i+3<=m&&get<2>(rngs2[s[i]*100+s[i+1]*10+s[i+2]])!=-1)dp[i+3]=i;
    }
    if(dp[m]==-1){printf("-1\n");continue;}
    ress.clear();
    for(I i=m;i!=0;i=dp[i]){
      I j=dp[i];
      if(i-j==2)ress.push_back(rngs1[s[j]*10+s[j+1]]);
      if(i-j==3)ress.push_back(rngs2[s[j]*100+s[j+1]*10+s[j+2]]);
    }
    reverse(ress.begin(),ress.end());
    printf("%i\n",ress.size());
    for(auto[l,r,i]:ress)printf("%i %i %i\n",l+1,r+1,i+1);
  }
}