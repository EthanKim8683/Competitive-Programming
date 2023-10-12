#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I LOGN=17;
I a_arr[N];
I spas[N][LOGN];
map<I,Lli>cnts;
I n;
void bld(){
  for(I i=1;i<LOGN;i++)for(I j=0;j+(1<<i)<=n;j++)spas[j][i]=gcd(spas[j][i-1],spas[j+(1<<(i-1))][i-1]);
}
I qry(I l,I r){
  I d=31-__builtin_clz(r-l);
  return gcd(spas[l][d],spas[r-(1<<d)][d]);
}
I fnd(I i,I x){
  I l=0,r=i;
  while(l<r){
    I m=l+(r-l)/2;
    qry(m,i+1)>=x?r=m:l=m+1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)spas[i][0]=a_arr[i];
  bld();
  for(I i=0;i<n;i++){
    I x=a_arr[i],j=i;
    while(j>0&&x!=1){
      I k=fnd(i,x);
      cnts[x]+=j-k+1;
      j=k-1,x=qry(j,i+1);
    }
    cnts[qry(0,i+1)]+=j+1;
  }
  I q;cin>>q;
  while(q--){
    I x;cin>>x;
    printf("%lli\n",cnts[x]);
  }
}