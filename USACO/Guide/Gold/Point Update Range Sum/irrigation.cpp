#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
template<class T>
using ordered_set=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
using I=int;
using Lli=long long int;
using B=bool;
const I N=500000;
const I M=500000;
const I Q=500000;
I a_arr[N];
Lli qrys[Q];
I ress[Q];
I inds1[M],inds2[Q];
I cnts[M];
Lli csts[M];
ordered_set<I>inds;
B cmp1(I a,I b){
  return cnts[a]<cnts[b];
}
B cmp2(I a,I b){
  return qrys[a]<qrys[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,q;cin>>n>>m>>q;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<q;i++){
    Lli k;cin>>k;
    qrys[i]=k;
  }
  for(I i=0;i<n;i++)cnts[a_arr[i]-1]++;
  iota(inds1,inds1+m,0);
  sort(inds1,inds1+m,cmp1);
  csts[0]=n+1;
  for(I i=1;i<m;i++)csts[i]=(Lli)i*(cnts[inds1[i]]-cnts[inds1[i-1]])+csts[i-1];
  iota(inds2,inds2+q,0);
  sort(inds2,inds2+q,cmp2);
  Lli pre=0;
  for(I i=0,j=0;i<q;i++){
    Lli k=qrys[inds2[i]];
    for(;j<m&&csts[j]<=k;j++)inds.insert(inds1[j]),pre=csts[j];
    ress[inds2[i]]=*inds.find_by_order((k-pre)%inds.size());
  }
  for(I i=0;i<q;i++)printf("%i\n",ress[i]+1);
}