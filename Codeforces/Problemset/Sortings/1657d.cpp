#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=3e5;
const I C=1e6;
const I MIN=-1e9;
Lli facs[C+1],upps[C+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,c;cin>>n>>c;
  fill_n(facs,c+1,MIN),fill_n(upps,c+1,MIN);
  for(I i=0;i<n;i++){
    I c,d,h;cin>>c>>d>>h;
    facs[c]=max(facs[c],(Lli)d*h);
  }
  for(I i=1;i<=c;i++)for(I j=1;i*j<=c;j++)upps[i*j]=max(upps[i*j],facs[i]*j-1);
  for(I i=1;i+1<=c;i++)upps[i+1]=max(upps[i+1],upps[i]);
  I m;cin>>m;
  for(I i=0;i<m;i++){
    I d;Lli h;cin>>d>>h;
    Lli fac=d*h;I cst=lower_bound(upps+1,upps+c,fac)-upps;
    printf("%i ",upps[cst]<fac?-1:cst);
  }
}