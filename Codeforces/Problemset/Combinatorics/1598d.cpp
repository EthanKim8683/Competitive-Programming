#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
I a_arr[N];
I b_arr[N];
Lli cnts1[N+1],cnts2[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i]>>b_arr[i];
    fill_n(cnts1,n+1,0);
    fill_n(cnts2,n+1,0);
    for(I i=0;i<n;i++){
      cnts1[a_arr[i]]++;
      cnts2[b_arr[i]]++;
    }
    Lli res=1;
    for(I i=0;i<3;i++)res*=n-i;
    for(I i=1;i<=3;i++)res/=i;
    for(I i=0;i<n;i++){
      I a=a_arr[i],b=b_arr[i];
      res-=(cnts1[a]-1)*(cnts2[b]-1);
    }
    printf("%lli\n",res);
  }
}