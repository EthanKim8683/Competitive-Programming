#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
Lli ask(I l,I r){
  printf("? %i %i\n",l+1,r+1),fflush(stdout);
  Lli x;cin>>x;
  if(x==-1)exit(0);
  return x;
}
void ans(I i,I j,I k){
  printf("! %i %i %i\n",i+1,j+1,k+1),fflush(stdout);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    I l=0,r=n-1;
    while(l<r){
      I m=l+(r-l+1)/2;
      ask(0,m)==0?l=m:r=m-1;
    }
    I i=l,j=i+ask(i,n-1)-ask(i+1,n-1)+1,k=j+ask(j,n-1)-ask(j+1,n-1);
    ans(i,j,k);
  }
}
/*
i can be found using binary search for the greatest index without inversions

then, j can be found in two queries, as the number of inversions introduced
between [i + 1, n - 1] and [i, n - 1] is equal to j - 1 - i

finally, k can be found similar to j
*/