#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2000;
const I A=2000;
I a_arr[N];
I cnts[A+1];
Lli bins[A+1][A+1];
vector<I>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;Lli p;cin>>n>>p;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cnts[a_arr[i]]++;
  for(I i=0;i<=A;i++)bins[i][0]=1;
  for(I i=1;i<=A;i++)for(I j=i;j<=A;j++)bins[j][i]=bins[j-1][i-1]*j%p;
  for(I i=1;i<=A;i++){
    I acc=0;Lli cur=1;
    for(I j=A;j>=1;j--)(cur*=bins[max(n-max(j-i,0)-acc,0)][cnts[j]])%=p,acc+=cnts[j];
    if(cur!=0)ress.push_back(i);
  }
  printf("%i\n",ress.size());
  for(auto i:ress)printf("%i ",i);
}