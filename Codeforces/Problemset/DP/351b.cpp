#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=3000;
I fens[N+1];
I n;
void upd(I i,I val){
  for(;i<=n;i+=i&-i)fens[i]+=val;
}
I qry(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  I cnt=0;
  for(I i=0;i<n;i++){
    I p;cin>>p,p--;
    upd(p+1,1),cnt+=qry(n)-qry(p+1);
  }
  printf("%i\n",cnt/2*4+cnt%2);
}