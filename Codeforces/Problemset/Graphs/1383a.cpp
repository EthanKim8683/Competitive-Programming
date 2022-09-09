#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using S=string;
using B=bool;

vector<I>adjs[26];
B viss[26];
B rels[26];

I dfs(I a){
  if(viss[a])return 0;
  viss[a]=true;
  I res=1;
  for(auto b:adjs[a])res+=dfs(b);
  return res;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    S a;cin>>a;
    S b;cin>>b;
    for(I i=0;i<26;i++)adjs[i].clear();
    B res=true;
    for(I i=0;i<n;i++){
      I c=a[i]-'a',d=b[i]-'a';
      if(d<c)res=false;
      adjs[c].push_back(d);
      adjs[d].push_back(c);
      rels[c]=rels[d]=true;
    }
    if(!res){printf("-1\n");continue;}
    I cnt=0;
    fill_n(viss,26,false);
    for(I i=0;i<26;i++)
      if(rels[i]&&!viss[i])cnt+=dfs(i)-1;
    printf("%i\n",cnt);
  }
  return 0;
}