#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e6;
I a_arr[N];
map<I,I>cnts;
I frws[N],bkws[N];
I fens[N+1];
I n;
void upd(I i,I val){
  for(i++;i<=n;i+=i&-i)fens[i]+=val;
}
I qry(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)frws[i]=++cnts[a_arr[i]];
  cnts.clear();
  for(I i=n-1;i>=0;i--)bkws[i]=++cnts[a_arr[i]];
  for(I i=0;i<n;i++)upd(bkws[i]-1,1);
  Lli res=0;
  for(I i=0;i<n;i++){
    upd(bkws[i]-1,-1);
    res+=qry(frws[i]-1);
  }
  printf("%lli\n",res);
}