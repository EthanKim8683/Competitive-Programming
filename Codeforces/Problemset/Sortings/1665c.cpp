#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
I chds[N];
vector<I>rems;
I n;
I ovf(I x){
  I res=0;
  for(auto rem:rems)res+=max(rem-x,0);
  return res;
}
I fnd1(){
  I l=0,r=n;
  while(l<r){
    I m=l+(r-l)/2;
    ovf(m)<=m?r=m:l=m+1;
  }
  return l;
}
I fnd2(){
  I l=0,r=n;
  while(l<r){
    I m=l+(r-l+1)/2;
    ovf(m)>=m?l=m:r=m-1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    fill_n(chds,n,0);
    for(I i=1;i<n;i++){
      I p;cin>>p,p--;
      chds[p]--;
    }
    sort(chds,chds+n);
    I cnt=1;
    for(I i=0;i<n;i++)cnt+=chds[i]<0;
    rems.clear();
    for(I i=0;i<cnt;i++){
      I rem=max(-chds[i]-(cnt-i),0);
      if(rem>0)rems.push_back(rem);
    }
    I x1=fnd1(),x2=fnd2();
    printf("%i\n",cnt+min(max(x1,ovf(x1)),max(x2,ovf(x2))));
  }
}