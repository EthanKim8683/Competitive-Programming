#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=1e5;

I ps[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n=s.size();
  for(I i=0;i+1<n;i++)ps[i+1]=s[i]==s[i+1];
  for(I i=0;i+1<n;i++)ps[i+1]+=ps[i];
  I m;cin>>m;
  for(I i=0;i<m;i++){
    I l,r;cin>>l>>r;
    printf("%i\n",ps[r-1]-ps[l-1]);
  }
}