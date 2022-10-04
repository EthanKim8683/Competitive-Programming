#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

I adjs[26];
B inds[26];
B uses[26];
B viss1[26],viss2[26];
vector<I>tops;
vector<I>ress;
priority_queue<I>que;

void dfs(I a){
  if(a==-1)return;
  if(viss2[a])return;
  viss2[a]=1;
  ress.push_back(a);
  dfs(adjs[a]);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(adjs,26,-1);
  for(I i=0;i<n;i++){
    S s;cin>>s;
    I m=s.size();
    for(I j=0;j<m;j++)uses[s[j]-'a']=1;
    for(I j=0;j+1<m;j++){
      I a=s[j]-'a',b=s[j+1]-'a';
      if(adjs[a]!=-1&&adjs[a]!=b)printf("NO\n"),exit(0);
      adjs[a]=b;
      inds[b]=1;
    }
  }
  I cnt=0;
  for(I i=0;i<26;i++)cnt+=uses[i];
  for(I i=0;i<26;i++)if(uses[i]&&!inds[i])que.push(-i);
  while(que.size()){
    I a=-que.top();que.pop();
    if(viss1[a])printf("NO\n"),exit(0);
    viss1[a]=1;
    tops.push_back(a);
    I b=adjs[a];
    if(b!=-1)que.push(-b);
  }
  if(cnt!=tops.size())printf("NO\n"),exit(0);
  for(auto i:tops)dfs(i);
  for(auto i:ress)printf("%c",i+'a');
}