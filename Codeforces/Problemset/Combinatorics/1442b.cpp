#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=200000;
const I K=N-1;
const Lli MOD=998244353;
I a_arr[N];
I b_arr[K];
I inds[N+1];
map<I,I>rems;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<k;i++)cin>>b_arr[i];
    for(I i=0;i<n;i++)inds[a_arr[i]]=i;
    rems.clear();
    for(I i=0;i<n;i++)rems[i]=1;
    for(I i=0;i<k;i++)rems[inds[b_arr[i]]]=0;
    Lli res=1;
    for(I i=0;i<k;i++){
      I j=inds[b_arr[i]];
      auto it=rems.find(j);
      I cnt=0;
      if(it!=rems.begin())cnt+=prev(it)->second;
      if(next(it)!=rems.end())cnt+=next(it)->second;
      (res*=cnt)%=MOD;
      rems.erase(it);
    }
    printf("%lli\n",res);
  }
}
/*
say we colored the elements in array a depending on whether they need to be
preserved for insertion into b (red if true, black if false)

when inserting an a[i] into b, regardless of whether a[i + 1] or a[i - 1]
(both black) is deleted, the number of black elements beside the last and next
red elements is the same, since a[i] itself becomes a black element

this means each b[i] can be handled independently
*/