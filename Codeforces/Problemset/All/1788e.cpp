#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const I MIN=-1e9;
I a_arr[N];
Lli ps[N+1];
vector<Lli>cpss;
I segs[2*(N+1)];
void upd(I i,I val){
  i+=cpss.size();
  for(segs[i]=max(segs[i],val);i>>=1;)segs[i]=max(segs[i<<1],segs[i<<1|1]);
}
I qry(I l,I r){
  I res=MIN;
  for(l+=cpss.size(),r+=cpss.size();l<r;l>>=1,r>>=1){
    if(l&1)res=max(res,segs[l++]);
    if(r&1)res=max(res,segs[--r]);
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)ps[i+1]=ps[i]+a_arr[i];
  for(I i=0;i<=n;i++)cpss.push_back(ps[i]);
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  fill_n(segs,2*cpss.size(),MIN);
  I acc=0;
  for(I i=0;i<=n;i++){
    I cur=lower_bound(cpss.begin(),cpss.end(),ps[i])-cpss.begin();
    acc=max(acc,qry(0,cur+1)+i);
    upd(cur,acc-i);
  }
  printf("%i\n",acc);
}
/*
if we take the prefix sum at every element, a subarray has non-negative sum
if its right bound's prefix sum is greater than or equal to its left bound's

using coordinate compression, we can compress the prefix sums and use dynamic
programming and point update range query to transition from all prefix sums
less than or equal to the current one

we can also use index costs to add the length of each transition
*/