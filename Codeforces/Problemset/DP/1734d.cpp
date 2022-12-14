#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=200000;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k,k--;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I l=k,r=k;
    Lli cur=a_arr[k];
    B res=k==0||k==n-1;
    while(1){
      Lli tmp1=cur;
      pair<Lli,I>mov1={cur,r};
      for(I i=r+1;i<n;i++){
        tmp1+=a_arr[i];
        if(tmp1<0)break;
        res|=i==n-1;
        if(tmp1>=mov1.first)mov1={tmp1,i};
      }
      Lli tmp2=cur;
      pair<Lli,I>mov2={cur,l};
      for(I i=l-1;i>=0;i--){
        tmp2+=a_arr[i];
        if(tmp2<0)break;
        res|=i==0;
        if(tmp2>=mov2.first)mov2={tmp2,i};
      }
      auto[sum1,idx1]=mov1;
      auto[sum2,idx2]=mov2;
      if(idx1==r&&idx2==l)break;
      cur+=sum1-cur+sum2-cur;
      r=idx1,l=idx2;
    }
    printf("%s\n",res?"YES":"NO");
  }
}