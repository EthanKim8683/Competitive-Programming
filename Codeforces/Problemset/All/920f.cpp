#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=3e5;
const I LOGN=19;
const I FIXN=1<<LOGN;
const I A=1e6;
I a_arr[N];
I cnts[A+1];
set<I>rems;
Lli fens[N+1];
I n;
void upd(I i,I val){
  for(;i<=n;i+=i&-i)fens[i]+=val;
}
Lli qry(I i){
  Lli res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  for(I i=1;i<=A;i++)for(I j=i;j<=A;j+=i)cnts[j]++;
  I m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)rems.insert(i),upd(i+1,a_arr[i]);
  while(m--){
    I t,l,r;cin>>t>>l>>r,l--,r--;
    if(t==1){
      auto low=rems.lower_bound(l),upp=rems.upper_bound(r);
      for(auto it=low;it!=upp;){
        I i=*it,a=a_arr[i],b=cnts[a];
        upd(i+1,b-a),a_arr[i]=b;
        it=b==1||b==2?rems.erase(it):next(it);
      }
    }
    if(t==2){
      printf("%lli\n",qry(r+1)-qry(l));
    }
  }
}