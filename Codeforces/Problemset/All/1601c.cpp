#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e6;
const I M=1e6;
const I MAX=1e9;
const I LOGN=20;
const I POWN=1<<LOGN;
I a_arr[N];
I b_arr[M];
I inds[N];
I vals[2*POWN],dels[2*POWN];
I fens[N+1];
I lgn,pwn;
I n;
void app(I i,I val){
  vals[i]+=val;
  if(i<pwn)dels[i]+=val;
}
void psh(I i){
  for(I j=lgn;j>0;j--){
    I k=(i+pwn)>>j;
    if(dels[k])app(k<<1,dels[k]),app(k<<1|1,dels[k]),dels[k]=0;
  }
}
void pll(I i){
  for(i+=pwn;i>>=1;)vals[i]=min(vals[i<<1],vals[i<<1|1])+dels[i];
}
void upd1(I l,I r,I val){
  psh(l),psh(r-1);
  for(I i=l+pwn,j=r+pwn;i<j;i>>=1,j>>=1){
    if(i&1)app(i++,val);
    if(j&1)app(--j,val);
  }
  pll(l),pll(r-1);
}
I qry1(I l,I r){
  psh(l),psh(r-1);
  I res=MAX;
  for(I i=l+pwn,j=r+pwn;i<j;i>>=1,j>>=1){
    if(i&1)res=min(res,vals[i++]);
    if(j&1)res=min(res,vals[--j]);
  }
  return res;
}
void upd2(I i,I val){
  for(;i<=n;i+=i&-i)fens[i]+=val;
}
I qry2(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I m;cin>>n>>m;
    lgn=31-__builtin_clz(2*(n+1)-1),pwn=1<<lgn;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<m;i++)cin>>b_arr[i];
    sort(b_arr,b_arr+m);
    iota(inds,inds+n,0);
    sort(inds,inds+n,[&](I i,I j){
      I a=a_arr[i],b=a_arr[j];
      return a==b?i<j:a<b;
    });
    fill_n(vals,2*pwn,0);
    fill_n(dels,2*pwn,0);
    for(I i=0;i<n;i++)upd1(i+1,pwn,1);
    Lli res=0;
    for(I i=0,j=0,k=0;i<m;i++){
      for(;j<n;j++){
        I l=inds[j];
        if(a_arr[l]>b_arr[i])break;
        upd1(l+1,pwn,-1);
      }
      for(;k<n;k++){
        I l=inds[k];
        if(a_arr[l]>=b_arr[i])break;
        upd1(0,l+1,1);
      }
      res+=qry1(0,pwn);
    }
    fill_n(fens,n+1,0);
    for(I i=0;i<n;i++){
      I j=inds[i];
      res+=i-qry2(j+1),upd2(j+1,1);
    }
    printf("%lli\n",res);
  }
}
/*
any (j, k) such that b[j] > a[k] can be resolved by increasing inds[j]

furthermore, all (k, j) such that a[k] > b[j], assuming inds[i] is optimal,
are outweighed by all (k, l, j) such that a[l] < b[i] < b[j], meaning never
would it be optimal to decrease inds[j] (at least not before inds[i])

this means we can effectively solve each b[i] independently and only care
about possible inversions with a since there will never be inversions
between members of array b
*/