#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
I x_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,d;cin>>n>>d;
  for(I i=0;i<n;i++)cin>>x_arr[i];
  Lli res=0;
  for(I l=0,r=0;r<n;r++){
    while(x_arr[r]-x_arr[l]>d)l++;
    Lli len=r-l;
    res+=len*(len-1)/2;
  }
  printf("%lli\n",res);
}