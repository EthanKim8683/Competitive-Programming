#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=20;
Lli facs[N+1];
Lli bin(I n,I k){
  return facs[n]/facs[k]/facs[n-k];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i;
  I n;cin>>n;
  Lli res=0;
  for(I i=1;i<=n/2;i++)res+=bin(n/2-1,i-1)*facs[i-1]*facs[n-2-(i-1)];
  printf("%lli\n",res);
}
/*
in each dance, we can assign the participant with the smallest number as the
first participant

in the first dance, the smallest number is always 1

therefore, we can iterate through all possible smallest numbers in the second
dance
*/