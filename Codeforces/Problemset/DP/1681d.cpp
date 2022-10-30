#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

const I N=10000;

map<Lli,I>dp;
queue<Lli>que;

I len(Lli x){
  I len=1;
  while(x/=10)len++;
  return len;
}

I main(){
  I n;Lli x;cin>>n>>x;
  dp[x]=0,que.push(x);
  while(que.size()){
    Lli a=que.front();que.pop();
    if(len(a)==n)printf("%i\n",dp[a]),exit(0);
    for(Lli t=a;t;t/=10){
      Lli b=a*(t%10);
      if(b<=a)continue;
      if(len(b)>n)continue;
      if(dp.count(b))continue;
      dp[b]=dp[a]+1,que.push(b);
    }
  }
  printf("-1\n");
}