#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using C=char;
const I N=1e5;
C ress[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill_n(ress,N+1,'a');
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k,k--;
    Lli l=0,r=n-2;
    while(l<r){
      Lli m=l+(r-l)/2,i=n-2-m;
      k>=i*(i+1)/2?r=m:l=m+1;
    }
    Lli i=n-2-l,j=n-1-(k-i*(i+1)/2);
    ress[l]=ress[j]='b',ress[n]=0;
    printf("%s\n",ress);
    ress[l]=ress[j]=ress[n]='a';
  }
}
/*
using combinatorics, we can find the number of strings such that the "leading
b" is before index x

if the number of strings with leading b less than x does not exceed k and is
the maximum possible, the kth string has the same leading b

the second b can be found easily
*/