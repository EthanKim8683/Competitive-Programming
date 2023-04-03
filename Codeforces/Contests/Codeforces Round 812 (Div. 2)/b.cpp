#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;

const I N=1e5;

I a_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I i=0;
    while(i+1<n&&a_arr[i+1]>=a_arr[i])i++;
    while(i+1<n&&a_arr[i+1]<=a_arr[i])i++;
    if(i==n-1)printf("YES\n");
    else printf("NO\n");
  }
  return 0;
}