#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;

const I N=1e5;

C s[N+1];
vector<I>grps;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    cin>>s;
    grps.clear();
    grps.push_back('0');
    for(I i=0;i<n;i++)if(grps.empty()||s[i]!=grps.back())grps.push_back(s[i]);
    printf("%i\n",max((I)grps.size()-2,0));
  }
}