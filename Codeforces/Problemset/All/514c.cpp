#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
const I N=3e5;
const I M=3e5;
const I L=6e5;
S mems[N];
S qrys[M];
I nods[L+N][27];
I cur=0;
I dep=0;
S str;
void add(S s){
  I i=0;
  for(auto c:s){
    c-='a';
    if(nods[i][c]==-1)i=nods[i][c]=++cur;
    else i=nods[i][c];
  }
  if(nods[i][26]==-1)nods[i][26]=++cur;
}
B dfs(I i,I t){
  if(i==-1)return 0;
  if(dep>=str.size())return nods[i][26]!=-1&&t;
  I c=str[dep]-'a';
  if(t==0)for(I j=0;j<26;j++){
    dep++;B cur=dfs(nods[i][j],j!=c);dep--;
    if(cur)return 1;
  }
  if(t==1){
    dep++;B cur=dfs(nods[i][c],1);dep--;
    if(cur)return 1;
  }
  return 0;
}
B qry(S s){
  str=s;
  return dfs(0,0);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&nods[0][0],&nods[0][0]+L*27,-1);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>mems[i];
  for(I i=0;i<m;i++)cin>>qrys[i];
  for(I i=0;i<n;i++)add(mems[i]);
  for(I i=0;i<m;i++)printf("%s\n",qry(qrys[i])?"YES":"NO");
}