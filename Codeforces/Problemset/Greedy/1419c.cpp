#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e3;

I a_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,x;cin>>n>>x;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n);
    if(a_arr[0]==x&&a_arr[n-1]==x){printf("0\n");continue;}
    if(binary_search(a_arr,a_arr+n,x)){printf("1\n");continue;}
    I sum=accumulate(a_arr,a_arr+n,0);
    if(x*n==sum){printf("1\n");continue;}
    printf("2\n");
  }
}