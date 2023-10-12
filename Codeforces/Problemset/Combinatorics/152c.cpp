#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using Lli=long long int;
const I N=100;
const I M=100;
const Lli MOD=1e9+7;
C nams[N][M+1];
set<C>unqs[M];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>nams[i];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)unqs[j].insert(nams[i][j]);
  Lli res=1;
  for(I i=0;i<m;i++)(res*=unqs[i].size())%=MOD;
  printf("%lli\n",res);
}
/*
since we can swap individual characters of same index between names the number
of names possible in position 1 is the number of combinations of unique letters
at each index
*/