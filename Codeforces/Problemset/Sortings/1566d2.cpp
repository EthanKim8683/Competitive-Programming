#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=300;
const I M=300;
I a_arr[N*M];
I inds[N*M];
I fens[N*M+1];
I n,m;
B cmp1(I a,I b){
  return pair<I,I>{a_arr[a],a}<pair<I,I>{a_arr[b],b};
}
B cmp2(I a,I b){
  return pair<I,I>{a_arr[a],-a}<pair<I,I>{a_arr[b],-b};
}
void upd(I i,I val){
  for(;i<=n*m;i+=i&-i)fens[i]+=val;
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
    cin>>n>>m;
    for(I i=0;i<n*m;i++)cin>>a_arr[i];
    iota(inds,inds+n*m,0);
    sort(inds,inds+n*m,cmp1);
    Lli res=0;
    for(I i=0;i<n;i++){
      sort(inds+i*m,inds+(i+1)*m,cmp2);
      for(I j=0;j<m;j++)res+=qry(inds[i*m+j]),upd(inds[i*m+j]+1,1);
      for(I j=0;j<m;j++)upd(inds[i*m+j]+1,-1);
    }
    printf("%lli\n",res);
  }
}