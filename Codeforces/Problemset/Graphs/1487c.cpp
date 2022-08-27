#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;

const I N=100;

I vals[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    I m=n-1,j=0;
    for(I i=0;i<m/2;i++)vals[j++]=1;
    if((n-1)%2)vals[j++]=0;
    for(I i=0;i<m/2;i++)vals[j++]=-1;
    for(I i=0;i<n;i++)for(I j=0;j<n-i-1;j++)
      printf("%i ",vals[j]);
    printf("\n");
  }
  return 0;
}