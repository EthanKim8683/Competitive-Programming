#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=100000;
const I X=100000;

I x_arr[N];
I ps[X+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>x_arr[i];
  for(I i=0;i<n;i++)ps[x_arr[i]]++;
  for(I i=0;i<X;i++)ps[i+1]+=ps[i];
  I q;cin>>q;
  while(q--){
    I m;cin>>m;
    printf("%i\n",ps[min(m,X)]);
  }
}