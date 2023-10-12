#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=5e5;
I lcps[2*N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  S s;cin>>s,s+=s;
  for(I i=1,l=0,r=0;i<2*n;i++){
    if(i<r)lcps[i]=min(r-i,lcps[i-l]);
    while(i+lcps[i]<2*n&&s[lcps[i]]==s[i+lcps[i]])lcps[i]++;
    if(i+lcps[i]>r)l=i,r=i+lcps[i];
  }
  I siz=n;
  for(I i=1;i<n;i++)if(s[(i+lcps[i])%n]>s[lcps[i]%i]){siz=i;break;}
  S rep=s.substr(0,siz),res="";
  while(res.size()<k)res+=rep;
  while(res.size()>k)res.pop_back();
  printf("%s\n",res.c_str());
}