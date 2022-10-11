#include<bits/stdc++.h>

using namespace std;

using I=int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0,j=0;i<n;i++){
    I a=2*i,b=2*i+1;
    if(j<k)swap(a,b),j++;
    printf("%i %i ",a+1,b+1);
  }
}