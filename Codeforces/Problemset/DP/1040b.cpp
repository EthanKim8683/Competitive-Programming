#include<bits/stdc++.h>

using namespace std;

using I=int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  I rng=2*k+1;
  I upp=n/rng+!!(n%rng),low=upp-1;
  I cur=low*2*k+upp;
  I rem=(n-cur)/2;
  printf("%i\n",upp);
  for(I i=0;i<upp;i++){
    printf("%i ",rem+1);
    rem+=rng;
  }
}