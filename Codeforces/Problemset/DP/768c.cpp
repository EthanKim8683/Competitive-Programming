#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
const I K=1e5;
const I LOGA=10;
const I MIN=-1e9;
const I MAX=1e9;
I a_arr[N];
I dp[2][1<<LOGA];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k,x;cin>>n>>k>>x;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)dp[0][a_arr[i]]++;
  for(I i=0;i<k;i++){
    I cur=0;
    for(I j=0;j<(1<<LOGA);j++){
      I cnt=dp[i%2][j];
      dp[(i+1)%2][j]+=cnt/2+(cur%2)*cnt%2;
      dp[(i+1)%2][j^x]+=cnt/2+!(cur%2)*cnt%2;
      cur+=cnt;
    }
    for(I j=0;j<(1<<LOGA);j++)dp[i%2][j]=0;
  }
  I low=MAX,upp=MIN;
  for(I i=0;i<(1<<LOGA);i++){
    if(!dp[k%2][i])continue;
    low=min(low,i);
    upp=max(upp,i);
  }
  printf("%i %i\n",upp,low);
}