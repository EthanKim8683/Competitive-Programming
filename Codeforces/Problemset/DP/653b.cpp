#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using S=string;
using C=char;
struct Opr{S a,b;};

const I N=6,Q=36;

I dp[N+1][6];
Opr oprs[Q];
S cur;
I res=0;
I n,q;

void chk(){
  fill(&dp[0][0],&dp[0][0]+sizeof(dp)/sizeof(I),0);
  dp[1][cur[0]-'a']=1;
  for(I i=1;i<n;i++){
    for(I j=0;j<6;j++){
      S t="";
      t+=j+'a',t+=cur[i];
      for(I k=0;k<q;k++)if(t==oprs[k].a)
        dp[i+1][oprs[k].b[0]-'a']+=dp[i][j];
    }
  }
  res+=!!dp[n][0];
}

void dfs(I d){
  if(d==n){chk();return;}
  for(I i=0;i<6;i++){
    cur.push_back('a'+i);
    dfs(d+1);
    cur.pop_back();
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>q;
  for(I i=0;i<q;i++)cin>>oprs[i].a>>oprs[i].b;
  dfs(0);
  printf("%i\n",res);
  return 0;
}