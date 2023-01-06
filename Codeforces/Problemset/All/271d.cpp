#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using C=char;
using B=bool;
const I N=1500;
C typs[26+1];
I nods[N*N+1][26];
B viss[N*N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&nods[0][0],&nods[0][0]+(N*N+1)*26,-1);
  S s;cin>>s;
  cin>>typs;
  I k;cin>>k;
  I n=s.size();
  I res=0,upp=0;
  for(I i=0;i<n;i++){
    I cur=0,cnt=0;
    for(I j=i;j<n;j++){
      I c=s[j]-'a';
      cnt+=typs[c]!='1';
      if(cnt>k)break;
      if(nods[cur][c]==-1)cur=nods[cur][c]=++upp;
      else cur=nods[cur][c];
      if(viss[cur])continue;
      viss[cur]=1;
      res++;
    }
  }
  printf("%i\n",res);
}