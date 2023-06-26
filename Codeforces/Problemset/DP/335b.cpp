#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=5e4;
const I L=100;
const I MAX=1e9;
I cnts[26];
pair<I,I>dp[26*(L-1)+1][26*(L-1)][2];
set<I>incs1,incs2;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  for(auto c:s)cnts[c-'a']++;
  for(I i=0;i<26;i++)if(cnts[i]>=L){
    for(I j=0;j<L;j++)printf("%c",i+'a');
    exit(0);
  }
  I n=s.size();
  for(I i=0;i<n;i++){
    pair<I,I>acc1={2,MAX},acc2={0,MAX};
    for(I j=i-1;j>=0;j--){
      if(s[i]==s[j])dp[i+1][j][0]=max(dp[i+1][j][0],acc1);
      if(s[i]==s[j])dp[i+1][j][1]=max(dp[i+1][j][1],acc2);
      acc1=max(acc1,{dp[i][j][0].first+2,j});
      acc2=max(acc2,{dp[i][j][1].first+2,j});
      dp[i+1][j][0]=max(dp[i+1][j][0],{dp[i][j][0].first,j});
      dp[i+1][j][1]=max(dp[i+1][j][1],{dp[i][j][1].first,j});
    }
    dp[i+1][i][1]={1,MAX};
  }
  pair<I,I>res1={0,MAX},res2={0,MAX};
  for(I i=0;i<n;i++){
    res1=max(res1,{dp[n][i][0].first,i});
    res2=max(res2,{dp[n][i][1].first,i});
  }
  auto[len1,p1]=res1;auto[len2,p2]=res2;
  for(I i=n;i>0&&p1!=MAX;i--)incs1.insert(p1),p1=dp[i][p1][0].second;
  for(I i=n;i>0&&p2!=MAX;i--)incs2.insert(p2),p2=dp[i][p2][1].second;
  S hlf1="",hlf2="";
  for(auto i:incs1)hlf1+=S(1,s[i]);
  for(auto i:incs2)hlf2+=S(1,s[i]);
  S all1=hlf1,all2=hlf2;
  reverse(hlf1.begin(),hlf1.end());
  reverse(hlf2.begin(),hlf2.end());
  all1+=hlf1,all2+=hlf2.substr(1);
  if(all1.size()>all2.size()||all1.size()>=L){
    I off=max((I)(all1.size()-L)/2,0);
    printf("%s\n",all1.substr(off,L).c_str());
  }else{
    printf("%s\n",all2.c_str());
  }
}