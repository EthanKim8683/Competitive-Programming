#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=100000;

I ps[26][N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  S s;cin>>s;
  for(I i=0;i<n;i++)ps[s[i]-'a'][i+1]++;
  for(I i=0;i<26;i++)for(I j=0;j<n;j++)ps[i][j+1]+=ps[i][j];
  while(q--){
    I l,r;cin>>l>>r;
    I res=0;
    for(I i=0;i<26;i++)res+=(i+1)*(ps[i][r]-ps[i][l-1]);
    printf("%i\n",res);
  }
}