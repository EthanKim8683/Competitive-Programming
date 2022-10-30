#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1000;

I ress[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    I cur=0;
    for(I i=n-2;i>=0;i-=2)ress[i]=cur++;
    for(I i=n-1;i>=0;i-=2)ress[i]=cur++;
    for(I i=0;i<n;i++)printf("%i ",ress[i]+1);
    printf("\n");
  }
}