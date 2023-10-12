#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I A=1e5;
const Lli MOD=998244353;
I a_arr[N];
vector<I>divs[A+1];
I curs[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  for(I i=1;i<=A;i++){
    I j=1;
    divs[i].push_back(j);
    while(j<i){
      I low1=i/j,upp1=(i+j-1)/j,l=j+1,r=i+1;
      while(l<r){
        I m=l+(r-l)/2,low2=i/m,upp2=(i+m-1)/m;
        low1!=low2||upp1!=upp2?r=m:l=m+1;
      }
      j=l;
      divs[i].push_back(j);
    }
    divs[i].shrink_to_fit();
  }
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    Lli res=0,cur=0;
    for(I i=0;i<n;i++){
      I a=a_arr[i];
      curs[i]=0;
      for(I j=i-1;j>=0;j--){
        I b1=a_arr[j+1],k1=curs[j+1],l1=divs[b1][k1],low1=b1/l1;
        I b2=a_arr[j],k2=curs[j],l2=divs[b2][k2],upp2=(b2+l2-1)/l2;
        if(upp2<=low1)break;
        (cur-=(Lli)(divs[b2][k2]-1)*(j+1))%=MOD;
        for(;k2<divs[b2].size();k2++){
          I l3=divs[b2][k2],upp3=(b2+l3-1)/l3;
          if(upp3<=low1)break;
        }
        (cur+=(Lli)(divs[b2][k2]-1)*(j+1))%=MOD;
        curs[j]=k2;
      }
      (res+=cur)%=MOD;
    }
    printf("%lli\n",(res+MOD)%MOD);
  }
}
/*
first, operations can be used to divide a number into any number of parts
roughly evenly

second, an operation can only decrease values, so we can greedily perform
operations from right to left, ensuring that all parts of the current element
are non-decreasing and do not exceed the previous element

note that this means that subarrays sharing right bound share a suffix

this means that we can process the array a left to right, updating the prefix
based on the latest element and taking the sum of all suffixes of the current
prefix

this runs in O(N * sqrt(A)) time since each A, divided equally can only take
approximately sqrt(A) different values, 2 * sqrt(A) if the left and right
ends are different
*/