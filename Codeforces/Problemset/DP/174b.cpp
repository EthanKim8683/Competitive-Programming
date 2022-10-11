#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=4e5;

B dp[N+1][2];
I pars[N+1][2];
vector<pair<I,I>>ress;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n=s.size();
  dp[0][0]=1;
  for(I i=0;i<n;i++){
    if(dp[i][0])for(I j=0;j<8;j++){
      if(i+j+0>=n||s[i+j+0]=='.')break;
      dp[i+j+1][1]=1,pars[i+j+1][1]=j;
    }
    if(s[i]!='.')continue;
    if(dp[i][1])for(I j=0;j<3;j++){
      if(i+j+1>=n||s[i+j+1]=='.')break;
      dp[i+j+2][0]=1,pars[i+j+2][0]=j+1;
    }
  }
  if(!dp[n][0])printf("NO\n"),exit(0);
  I i=n,j=0;
  while(i!=0){
    I p=pars[i][j]+1;
    ress.push_back({i-=p,p}),j^=1;
  }
  reverse(ress.begin(),ress.end());
  printf("YES\n");
  for(I i=0;i<ress.size();i+=2){
    S res="";
    res+=s.substr(ress[i+0].first,ress[i+0].second);
    res+=s.substr(ress[i+1].first,ress[i+1].second);
    printf("%s\n",res.c_str());
  }
}