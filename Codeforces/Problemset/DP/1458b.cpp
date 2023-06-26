#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
const I N=100;
const I A=100;
const I MIN=-1e9;
pair<I,I>glss[N];
I dp[2][N+1][4*N*A+1];
deque<pair<I,I>>ques;
void cmb(I&a,I b){
  a=max(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+2*(N+1)*(4*N*A+1),MIN);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I a,b;cin>>a>>b;
    glss[i]={a,b};
  }
  dp[0][0][2*N*A]=0;
  for(I i=0;i<n;i++)for(I j=0;j<=i;j++){
    auto[a,b]=glss[i];
    for(I k=2*j*A;k>=-(i-j)*A;k--){
      I val=dp[i%2][j][2*N*A+k];
      while(ques.size()&&ques.front().first>k+b)ques.pop_front();
      while(ques.size()&&val+k>=ques.back().second)ques.pop_back();
      ques.push_back({k,val+k});
      cmb(dp[(i+1)%2][j][2*N*A+k],ques.front().second-k);
      cmb(dp[(i+1)%2][j+1][2*N*A+k+2*(a-b)],val+2*b);
      dp[i%2][j][2*N*A+k]=MIN;
    }
    for(I k=-(i-j)*A;k>=-(i-j+1)*A;k--){
      while(ques.size()&&ques.front().first>k+b)ques.pop_front();
      if(ques.size())cmb(dp[(i+1)%2][j][2*N*A+k],ques.front().second-k);
    }
    while(ques.size())ques.pop_front();
  }
  for(I i=1;i<=n;i++){
    I res=0;
    for(I j=0;j<=2*i*A;j++)res=max(res,dp[n%2][i][2*N*A+j]);
    printf("%.10Lf ",(Lf)res/2);
  }
}