#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
I a_arr[N];
I b_arr[N];
I fens[N+1];
vector<I>ress;
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
  I t;cin>>t;
  while(t--){
    cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)cin>>b_arr[i];
    fill_n(fens,n+1,0);
    for(I i=0;i<n;i++){
      I a=a_arr[i],b=b_arr[i];
      if(a<=b)continue;
      upd(a,1),upd(b,-1);
    }
    ress.clear();
    for(I i=1;i<=n;i++){
      B vld=1;
      for(I j=0;j<=n;j+=i)vld&=qry(min(j+i,n))-qry(j)==0;
      if(vld)ress.push_back(i);
    }
    printf("%i\n",ress.size());
    for(auto i:ress)printf("%i ",i);
    printf("\n");
  }
}
/*
a value k can be used to kill all bosses if, for all i such that a[i] > b[i],
both a[i] and b[i] are greater than k * j and less than or equal to k * (j + 1)
for some non-negative integer j

this is because, after the jth attempt Monocarp must be able to kill the ith
boss, so k * (j + 1) must be greater than or equal to a[i]

meanwhile, the boss must have yet to be killed by Polycarp, so k * j must be
less than b[i]
*/