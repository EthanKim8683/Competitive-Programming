#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=3000;
I a_arr[N];
I pres[(N+1)*(N+1)];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    Lli res=0;
    for(I i=0;i<n;i++){
      for(I j=i+1;j<n;j++)res+=pres[a_arr[i]*(n+1)+a_arr[j]];
      for(I j=0;j<i;j++)pres[a_arr[j]*(n+1)+a_arr[i]]++;
    }
    for(I i=0;i<n;i++)for(I j=i+1;j<n;j++)pres[a_arr[i]*(n+1)+a_arr[j]]=0;
    printf("%lli\n",res);
  }
}
/*
we can brute force for all ordered pairs (a[i], a[j])
*/