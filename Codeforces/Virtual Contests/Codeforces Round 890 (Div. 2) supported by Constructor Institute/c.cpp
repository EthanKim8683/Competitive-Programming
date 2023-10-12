#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1000;
const I MAX=1e9;
I a_arr[N];
I n,k;
B chk(I x){
  for(I i=0;i<n;i++){
    Lli tot=0;
    for(I j=0;i+j<n;j++){
      Lli cur=x-j-a_arr[i+j];
      if(cur<=0)return 1;
      tot+=cur;
      if(tot>k)break;
    }
  }
  return 0;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n>>k;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I l=*max_element(a_arr,a_arr+n),r=MAX;
    while(l<r){
      I m=l+(r-l+1)/2;
      chk(m)?l=m:r=m-1;
    }
    printf("%i\n",l);
  }
}