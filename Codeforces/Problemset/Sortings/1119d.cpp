#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=100000;
const I Q=100000;
const Lli MAX=2e18;
Lli s_arr[N];
Lli upps[N];
Lli qrys[Q];
I inds[Q];
Lli ress[Q];
B cmp(I a,I b){
  return qrys[a]<qrys[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>s_arr[i];
  sort(s_arr,s_arr+n);
  for(I i=0;i+1<n;i++)upps[i]=s_arr[i+1]-s_arr[i];
  upps[n-1]=MAX;
  sort(upps,upps+n);
  I q;cin>>q;
  for(I i=0;i<q;i++){
    Lli l,r;cin>>l>>r;
    qrys[i]=r-l+1;
  }
  iota(inds,inds+q,0);
  sort(inds,inds+q,cmp);
  Lli cur=0;
  for(I i=0,j=0;i<q;i++){
    while(j<n&&upps[j]<=qrys[inds[i]])cur+=upps[j++];
    ress[inds[i]]=cur+qrys[inds[i]]*(n-j);
  }
  for(I i=0;i<q;i++)printf("%lli ",ress[i]);
}