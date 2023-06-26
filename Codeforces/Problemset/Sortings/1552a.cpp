#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    S s;cin>>s;
    S v=s;
    sort(v.begin(),v.end());
    I res=0;
    for(I i=0;i<n;i++)res+=s[i]!=v[i];
    printf("%i\n",res);
  }
}