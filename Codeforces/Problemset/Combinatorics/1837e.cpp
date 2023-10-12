#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I K=19;
const Lli MOD=998244353;
I a_arr[1<<K];
I taks[K][1<<K];
I fixs[K][1<<K];
Lli facs[(1<<K)+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=(1<<K);i++)facs[i]=facs[i-1]*i%MOD;
  I k;cin>>k;
  for(I i=0;i<(1<<k);i++)cin>>a_arr[i];
  for(I i=0;i<(1<<k);i++){
    I a=a_arr[i]-1;
    if(a==0){
      for(I j=a;j<k;j++)taks[j][i>>(k-j)]++;
    }
    if(a>0){
      a=31-__builtin_clz(a);
      for(I j=a;j<k;j++)taks[j][i>>(k-j)]++;
      fixs[a][i>>(k-a)]++;
    }
  }
  Lli res=1;
  for(I i=0;i<k;i++){
    I cnt=0,rem=1<<i;
    for(I j=0;j<(1<<i);j++){
      rem-=fixs[i][j];
      if(fixs[i][j]>1)res=0;
      if(fixs[i][j]==1)continue;
      (res*=2-taks[i][j])%=MOD,cnt++;
    }
    (res*=facs[cnt])%=MOD;
    if(cnt!=rem)res=0;
  }
  printf("%lli\n",res);
}
/*
for the sake of convenience, "rank i" actually refers to place 2 ^ i + 2 for
i in [0, k - 1)

for the rigged rankings to hold true, no two teams with ranking i must be
in the same segment [j * siz, (j + 1) * siz), where j is some integer in
[0, 2 ^ i) and siz equals 2 ^ (k - i), otherwise one will rank over the other
before they are intended to play against each other
*/