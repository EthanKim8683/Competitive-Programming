#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;

const I N=2e5;

C cols[N+1];
vector<I>inds;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;C c;cin>>n>>c;
    cin>>cols;
    inds.clear();
    for(I i=0;i<n;i++)if(cols[i]=='g')inds.push_back(i),inds.push_back(i+n);
    sort(inds.begin(),inds.end());
    I res=0;
    for(I i=0;i<n;i++)if(cols[i]==c)res=max(res,*lower_bound(inds.begin(),inds.end(),i)-i);
    printf("%i\n",res);
  }
}