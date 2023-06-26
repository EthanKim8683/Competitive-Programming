#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1e5;
const I A=1e6;
const Lli MOD=1e9+7;
I a_arr[N];
Lli fens[A+2];
Lli pres[A+1];
void upd(I i,Lli val){
  for(val%=MOD;i<=A+1;i+=i&-i)(fens[i]+=val)%=MOD;
}
Lli qry(I i){
  Lli res=0;
  for(;i>0;i-=i&-i)(res+=fens[i])%=MOD;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  Lli res=0;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    upd(a+1,(qry(a+1)-qry(a))*(a-1));
    upd(a+1,(qry(a)+1)*a);
    (res+=qry(a+1)-qry(a)-pres[a])%=MOD;
    pres[a]=qry(a+1)-qry(a);
  }
  printf("%lli\n",(res+MOD)%MOD);
}