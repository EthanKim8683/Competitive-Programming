#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

I outs[26];
I inds[26];

B dfs(I a,I r){
  if(a==-1)return 0;
  if(r==a)return 1;
  return dfs(outs[a],r);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    fill_n(outs,26,-1);
    fill_n(inds,26,-1);
    I n;cin>>n;
    S s;cin>>s;
    for(auto c:s){
      if(outs[c-='a']!=-1)continue;
      for(I i=0;i<26;i++){
        if(inds[i]!=-1)continue;
        if(dfs(i,c))continue;
        inds[i]=c,outs[c]=i;
        break;
      }
    }
    I a=-1,b=-1;
    for(I i=0;i<26;i++)if(inds[i]!=-1&&outs[i]==-1)a=i;
    for(I i=0;i<26;i++)if(inds[i]==-1&&outs[i]!=-1)b=i;
    outs[a]=b,inds[b]=a;
    for(auto c:s)printf("%c",outs[c-'a']+'a');
    printf("\n");
  }
}