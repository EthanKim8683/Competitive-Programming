#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;
using Lli=long long int;

const I N=100;

C cels[N][N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>cels[i];
  Lli res=0;
  for(I i=0;i<n;i++){
    I sum1=0,sum2=0;
    for(I j=0;j<n;j++){
      sum1+=cels[i][j]=='C';
      sum2+=cels[j][i]=='C';
    }
    res+=(Lli)sum1*(sum1-1)/2;
    res+=(Lli)sum2*(sum2-1)/2;
  }
  printf("%lli\n",res);
}