#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
Lli a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr+1,a_arr+n);
    for(I i=1;i<n;i++){
      Lli dif=a_arr[i]-a_arr[0];
      if(dif>0)a_arr[0]+=dif-dif/2;
    }
    printf("%lli\n",a_arr[0]);
  }
}