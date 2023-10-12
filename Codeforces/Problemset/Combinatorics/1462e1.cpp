#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n);
    Lli res=0;
    for(I l=0,r=0;r<n;r++){
      while(a_arr[r]-a_arr[l]>2)l++;
      I len=r-l;
      res+=(Lli)len*(len-1)/2;
    }
    printf("%lli\n",res);
  }
}
/*
if we sort the array, we can think of every i, j, k as subsets of a range of
indices such that the difference between the values corresponding to the
minimum and maximum indices does not exceed 2
*/