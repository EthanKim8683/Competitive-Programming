#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I K=10;
Lli fens[K+1][N+1];
I n;
void upd(I i,I j,Lli val){
  for(;j<=n;j+=j&-j)fens[i][j]+=val;
}
Lli qry(I i,I j){
  Lli res=0;
  for(;j>0;j-=j&-j)res+=fens[i][j];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k;cin>>n>>k;
  for(I i=0;i<n;i++){
    I a;cin>>a,a--;
    upd(0,a+1,1);
    for(I j=1;j<=k;j++)upd(j,a+1,qry(j-1,a));
  }
  printf("%lli\n",qry(k,n));
}