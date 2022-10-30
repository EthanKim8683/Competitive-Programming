#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

I p_arr[N];
I inds[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++){I p;cin>>p,p_arr[i]=p-1;}
    for(I i=0;i<n;i++)inds[p_arr[i]]=i;
    B vld=1;
    I upp=n-1;
    for(I i=0;i<n;i++){
      I r=upp;
      while(i<n&&inds[i]==r)r--,i++;
      I l=inds[i];
      upp=l-1;
      while(i<n&&l<r)vld&=inds[i+1]==inds[i]+1,l++,i++;
    }
    printf("%s\n",vld?"Yes":"No");
  }
}