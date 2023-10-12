#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I K=5;
I a_arr[N][K];
array<pair<I,I>,1<<K>segs[2*N];
I n,k;
I dis(I x,I y){
  I res=0;
  for(I i=0;i<k;i++)res+=abs(a_arr[x][i]-a_arr[y][i]);
  return res;
}
I cst(I i,I msk){
  I res=0;
  for(I j=0;j<K;j++)res+=(msk>>j&1?1:-1)*a_arr[i][j];
  return res;
}
array<pair<I,I>,1<<K>cmb(array<pair<I,I>,1<<K>lhss,array<pair<I,I>,1<<K>rhss){
  array<pair<I,I>,1<<K>ress;
  for(I i=0;i<(1<<K);i++)ress[i]=max(lhss[i],rhss[i]);
  return ress;
}
void bld(){
  for(I i=0;i<n;i++)for(I j=0;j<(1<<K);j++)segs[i+n][j]={cst(i,j),i};
  for(I i=n-1;i>0;i--)segs[i]=cmb(segs[i<<1],segs[i<<1|1]);
}
void upd(I i){
  for(I j=0;j<(1<<K);j++)segs[i+n][j]={cst(i,j),i};
  for(i+=n;i>>=1;)segs[i]=cmb(segs[i<<1],segs[i<<1|1]);
}
I qry(I l,I r){
  array<pair<I,I>,1<<K>ress;
  for(I i=0;i<(1<<K);i++)ress[i]={cst(l,i),l};
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)ress=cmb(ress,segs[l++]);
    if(r&1)ress=cmb(ress,segs[--r]);
  }
  I res=0;
  for(I i=0;i<(1<<K);i++)res=max(res,dis(ress[i].second,ress[i^((1<<K)-1)].second));
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>k;
  for(I i=0;i<n;i++)for(I j=0;j<k;j++)cin>>a_arr[i][j];
  bld();
  I q;cin>>q;
  while(q--){
    I t;cin>>t;
    if(t==1){
      I i;cin>>i,i--;
      for(I j=0;j<k;j++)cin>>a_arr[i][j];
      upd(i);
    }
    if(t==2){
      I l,r;cin>>l>>r,l--;
      printf("%i\n",qry(l,r));
    }
  }
}
/*
we can use segment tree where each segment store the furthest points along
each facet of a k-dimensional hyper-rhombus and find the maximum distance
between points on opposite facets
*/