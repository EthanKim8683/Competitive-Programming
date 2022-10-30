#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=1e6;
const I X=1e7;

I x_arr[N];
B coms[X+1];
I cnts[X+1];
I ps[X+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>x_arr[i];
  for(I i=0;i<n;i++)cnts[x_arr[i]]++;
  for(I i=2;i<=X;i++)if(!coms[i])for(I j=i;j<=X;j+=i)ps[i+1]+=cnts[j],coms[j]=1;
  for(I i=0;i<X;i++)ps[i+1]+=ps[i];
  I m;cin>>m;
  for(I i=0;i<m;i++){
    I l,r;cin>>l>>r;
    printf("%i\n",ps[min(r+1,X)]-ps[min(l,X)]);
  }
}