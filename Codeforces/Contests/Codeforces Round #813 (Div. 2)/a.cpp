#include<iostream>
#include<cstdio>

using namespace std;

using I=int;

const I N=100;

I p_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>p_arr[i];
    I cnt=0;
    for(I i=0;i<k;i++)cnt+=p_arr[i]>k;
    printf("%i\n",cnt);
  }
  return 0;
}