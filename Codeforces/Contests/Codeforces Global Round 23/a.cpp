#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=50;

I a_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n);
    printf("%s\n",binary_search(a_arr,a_arr+n,1)?"YES":"NO");
  }
}