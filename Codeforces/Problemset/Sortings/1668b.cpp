#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n);
    Lli tot=n+a_arr[n-1];
    for(I i=1;i<n;i++)tot+=a_arr[i];
    printf("%s\n",tot<=m?"YES":"NO");
  }
}