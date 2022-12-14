#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
const I N=1000;
const I MAX=1e9;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S s;cin>>s;
  I a=0,b=0;
  B yes=1;
  S t=s;
  while(yes){
    yes=0;
    for(I i=0;i+1<n;i++)if(t[i]==t[i+1]){
      t[i]='0'+i%2;
      t[i+1]='0'+1-i%2;
      yes=1;
      break;
    }
    a+=yes;
  }
  yes=1;
  t=s;
  while(yes){
    yes=0;
    for(I i=0;i+1<n;i++)if(t[i]==t[i+1]){
      t[i]='0'+1-i%2;
      t[i+1]='0'+i%2;
      yes=1;
      break;
    }
    b+=yes;
  }
  printf("%i\n",min(a,b));
}