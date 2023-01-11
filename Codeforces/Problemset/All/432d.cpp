#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=1e5;
I zfns[N];
I ps[N+1];
vector<pair<I,I>>ress;
void bld(S s){
  I n=s.size();
  zfns[0]=n;
  for(I i=1,l=0,r=0;i<n;i++){
    if(i<=r)zfns[i]=min(r-i+1,zfns[i-l]);
    while(i+zfns[i]<n&&s[zfns[i]]==s[i+zfns[i]])zfns[i]++;
    if(i+zfns[i]-1>r)l=i,r=i+zfns[i]-1;
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n=s.size();
  bld(s);
  for(I i=0;i<n;i++)ps[zfns[i]]++;
  for(I i=n;i-1>=1;i--)ps[i-1]+=ps[i];
  for(I i=n-1;i>=0;i--){
    I z=zfns[i];
    if(i+z!=n)continue;
    ress.push_back({z,ps[z]});
  }
  printf("%i\n",ress.size());
  for(auto[l,c]:ress)printf("%i %i\n",l,c);
}