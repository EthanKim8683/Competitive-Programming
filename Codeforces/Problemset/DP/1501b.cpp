#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=2e5;

I ps[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    fill_n(ps,n+1,0);
    for(I i=0;i<n;i++){
      I a;cin>>a;
      ps[i+1]--;
      ps[max(i+1-a,0)]++;
    }
    for(I i=0;i<n;i++)ps[i+1]+=ps[i];
    for(I i=0;i<n;i++)printf("%i ",!!ps[i]);
    printf("\n");
  }
}