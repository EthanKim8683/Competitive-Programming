#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=2e5;
const I MAX=1e9;
pair<I,I>emps[N];
I n;Lli s;
B chk(I x){
  Lli tot=0;I abv=0;
  for(I i=n-1;i>=0;i--){
    auto[l,r]=emps[i];
    if(abv<n/2+1&&r>=x)tot+=max(l,x),abv++;
    else tot+=l;
  }
  return abv==n/2+1&&tot<=s;
}
I fnd(){
  I l=0,r=MAX;
  while(l<r){
    I m=l+(r-l+1)/2;
    chk(m)?l=m:r=m-1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n>>s;
    for(I i=0;i<n;i++){
      I l,r;cin>>l>>r;
      emps[i]={l,r};
    }
    sort(emps,emps+n);
    printf("%i\n",fnd());
  }
}