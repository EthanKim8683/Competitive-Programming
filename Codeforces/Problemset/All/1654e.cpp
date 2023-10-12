#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
const I A=1e5;
const I K=317;
I a_arr[N];
I pres[(A+N*K)*2+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I res=1;
  for(I i=-K;i<=K;i++){
    for(I j=0;j<n;j++)res=max(res,pres[a_arr[j]-i*j+A+N*K]+=1);
    for(I j=0;j<n;j++)pres[a_arr[j]-i*j+A+N*K]=0;
  }
  for(I i=0;i<n;i++){
    for(I j=1;j<=K&&i+j<n;j++){
      I dif=a_arr[i+j]-a_arr[i];
      if(dif%j==0)res=max(res,(pres[dif/j+A+N*K]+=1)+1);
    }
    for(I j=1;j<=K&&i+j<n;j++){
      I dif=a_arr[i+j]-a_arr[i];
      if(dif%j==0)pres[dif/j+A+N*K]=0;
    }
  }
  printf("%i\n",n-res);
}
/*
note that the maximum length of an arithmetic progression of common difference
x such that all elements are within [1, A] is A / x

we can then handle each x using one of two cases:

for all x <= sqrt(A), we can find the maximum number of occurences of
a[i] - i * x

for all x > sqrt(A), we can look for the most common common difference for all
j in [i + 1, i + sqrt(A)] for each i
*/