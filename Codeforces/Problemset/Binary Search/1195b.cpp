#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

I n,k;

I fnd(){
  I l=0,r=n;
  while(l<=r){
    I m=l+(r-l)/2;
    Lli a=n-m;
    Lli b=a*(a+1)/2-m;
    if(b==k)return m;
    if(b>k)l=m+1;
    if(b<k)r=m-1;
  }
  return -1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>k;
  printf("%i\n",fnd());
}