#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=500;
const I MAX=1e9;
I dp[N][N];
void cmb(I&a,I b){
  a=min(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+N*N,MAX);
  S s;cin>>s;
  I n=s.size();
  for(I i=1;i<n;i++)for(I j=0;j+i<n;j++){
    for(I k=0;k<i;k++){

    }
  }
}