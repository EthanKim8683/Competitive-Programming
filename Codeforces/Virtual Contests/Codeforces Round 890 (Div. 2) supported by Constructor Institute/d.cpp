#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2000;
I qry(I l,I r){
  if(l==r)return 0;
  printf("? %i %i\n",l+1,r+1),fflush(stdout);
  I res;cin>>res;
  if(res==-1)exit(0);
  return res;
}
void ans(I i){
  printf("! %i\n",i+1),fflush(stdout);
}
I slv(I l,I r){
  return qry(l,r)==qry(l,r-1)?r:l;
}
I dfs(I l,I r){
  if(r-l==0)return l;
  if(r-l==1)return qry(l,r)?l:r;
  I m=l+(r-l)/2;
  return slv(dfs(l,m),dfs(m+1,r));
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    ans(dfs(0,n-1));
  }
}