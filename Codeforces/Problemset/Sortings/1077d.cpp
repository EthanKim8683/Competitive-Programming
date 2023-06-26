#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
const I S=2e5;
I s_arr[N];
I cnts[S+1];
I inds[S+1];
vector<I>ress;
I n,k;
B cmp(I a,I b){
  return cnts[a]>cnts[b];
}
B chk(I x){
  I cnt=0;
  for(I i=0;i<k;i++)cnt+=cnts[inds[i]]/x;
  return cnt>=k;
}
I fnd(){
  I l=0,r=n;
  while(l<r){
    I m=l+(r-l+1)/2;
    chk(m)?l=m:r=m-1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>k;
  for(I i=0;i<n;i++)cin>>s_arr[i];
  for(I i=0;i<n;i++)cnts[s_arr[i]]++;
  iota(inds,inds+S+1,0);
  sort(inds,inds+S+1,cmp);
  I x=fnd(),rem=k;
  for(I i=0;i<k;i++){
    I dif=min(rem,cnts[inds[i]]/x);
    rem-=dif;
    for(I j=0;j<dif;j++)ress.push_back(inds[i]);
  }
  for(auto i:ress)printf("%i ",i);
}