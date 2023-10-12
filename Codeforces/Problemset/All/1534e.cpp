#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=500;
const I D=500;
I dp[D+1][N+1];
I eves[D];
I rems[N];
I inds[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(D+1)*(N+1),-1);
  I n,k;cin>>n>>k;
  dp[0][n]=1;
  I cnt=-1;
  for(I i=0;i<=D;i++){
    if(dp[i][0]!=-1){cnt=i;break;}
    if(i+1<=D)for(I j=0;j<=n;j++)if(dp[i][j]!=-1)for(I l=0;l<=min(j,k);l++)if(n-j>=k-l)dp[i+1][j-l+k-l]=l;
  }
  if(cnt==-1)printf("-1"),fflush(stdout),exit(0);
  for(I i=cnt,j=0;i>0;i--){
    I l=dp[i][j];
    eves[i-1]=l,j=j+l-k+l;
  }
  for(I i=0;i<cnt;i++)for(I j=0,eve=eves[i],odd=k-eve;j<n;j++){
    if(eve>0&&rems[j]%2==0)rems[j]++,eve--;
    else if(odd>0&&rems[j]%2==1)rems[j]++,odd--;
  }
  I res=0;
  iota(inds,inds+n,0);
  for(I i=0;i<cnt;i++){
    sort(inds,inds+n,[&](I a,I b){
      return rems[a]>rems[b];
    });
    printf("?");
    for(I j=0;j<k;j++){
      I l=inds[j];
      printf(" %i",l+1),rems[l]--;
    }
    printf("\n"),fflush(stdout);
    I cur;cin>>cur;
    res^=cur;
  }
  printf("! %i\n",res),fflush(stdout);
}
/*
since all elements must contribute to the final xor sum an odd number of
times, we can use dynamic programming keeping track of the number of elements
with either parity of contribution until entirely odd contribution is reached
*/