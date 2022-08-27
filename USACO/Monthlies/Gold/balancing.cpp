#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
struct Bnd{I l,r;};

const I N=1e5;

I p_arr[N-1];
Bnd bnds[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t,b;cin>>t>>b;
  while(t--){
    I n;cin>>n;
    for(I i=1;i<n;i++){I p;cin>>p,p_arr[i]=p-1;}
    for(I i=0;i<n;i++)cin>>bnds[i].l>>bnds[i].r;
    
  }
  return 0;
}