#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=10000;
const I M=100000;
const I L=1000000;
S w_arr[M];
I nods[L+1][27];
I dp[N+1];
vector<I>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&nods[0][0],&nods[0][0]+(L+1)*27,-1);
  I n;cin>>n;
  S t;cin>>t;
  I m;cin>>m;
  I cur=0;
  for(I i=0;i<m;i++){
    S w;cin>>w;
    w_arr[i]=w;
    reverse(w.begin(),w.end());
    I j=0;
    for(auto c:w){
      c=tolower(c)-'a';
      if(nods[j][c]==-1)nods[j][c]=++cur;
      j=nods[j][c];
    }
    if(nods[j][26]==-1)nods[j][26]=-2-i;
  }
  fill_n(dp,n+1,-1);
  dp[0]=0;
  for(I i=0;i<n;i++){
    if(dp[i]==-1)continue;
    I j=0;
    for(I k=i;k<n;k++){
      I c=t[k]-'a';
      if(nods[j][c]==-1)break;
      j=nods[j][c];
      if(nods[j][26]!=-1)dp[k+1]=-nods[j][26]-2;
    }
  }
  I i=n;
  while(i!=0){
    I j=dp[i];
    ress.push_back(j);
    i-=w_arr[j].size();
  }
  reverse(ress.begin(),ress.end());
  for(auto i:ress)printf("%s ",w_arr[i].c_str());
}