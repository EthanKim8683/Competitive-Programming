#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
const I N=1e4;
B dp[N+1][2];
set<S>ress;
set<S>curs;
void add(S s){
  reverse(s.begin(),s.end());
  ress.insert(s);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n=s.size();
  reverse(s.begin(),s.end());
  if(2<=n-5)dp[2][0]=1,add(s.substr(0,2));
  if(3<=n-5)dp[3][1]=1,add(s.substr(0,3));
  for(I i=2;i<n-5;i++){
    if(i+2<=n-5){
      S t=s.substr(i,2);
      B vld=0;
      if(dp[i][0]&&i-2>=0)vld|=s.substr(i-2,2)!=t;
      if(dp[i][1]&&i-3>=0)vld|=s.substr(i-3,3)!=t;
      if(vld)dp[i+2][0]=1,add(t);
    }
    if(i+3<=n-5){
      S t=s.substr(i,3);
      B vld=0;
      if(dp[i][0]&&i-2>=0)vld|=s.substr(i-2,2)!=t;
      if(dp[i][1]&&i-3>=0)vld|=s.substr(i-3,3)!=t;
      if(vld)dp[i+3][1]=1,add(t);
    }
  }
  printf("%i\n",ress.size());
  for(auto res:ress)printf("%s\n",res.c_str());
}