#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using C=char;
using B=bool;

const I N=500;
const I MOD=1e9+7;

C cels[N][N+1];
I dp[N][N];
I n;

B bnd(I i,I j){
  return i>=0&&i<n&&j>=0&&j<n;
}

pair<I,I>trn(I i,I j,I s){
  if(s==0)return{(n-1)-i-j,j};
  if(s==1)return{(n-1)+i-j,j};
  return{-1,-1};
}

pair<I,I>rev(I i,I j,I s){
  if(s==0)return{(n-1)-i-j,j};
  if(s==1)return{i+j-(n-1),j};
  return{-1,-1};
}

B bnd(I i,I j,I s){
  if(s==0){I k=n-i-j-1;return bnd(k,j);}
  if(s==1){I k=i+j-n+1;return bnd(k,j);}
  return false;
}

void add(I i,I j,I s,I v){
  auto[a,b]=rev(i+(s==1)-(s==0),j,s);
  auto[c,d]=rev(i,j+(s==1)-(s==0),s);
  if(bnd(a,b,s))dp[a][b]+=v;
  if(bnd(c,d,s))dp[c][d]+=v;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++)cin>>cels[i];
  fill_n(dp[0],n,1);
  for(I i=0;i<n;i++){
    for(I j=0;j<n-i;j++){
      auto[a,b]=trn(i,j,0);
      auto[c,d]=trn(i,j,1);
      printf("%c%c (%i %i, %i %i, %i %i) ",cels[a][b],cels[c][d],i,j,a,b,c,d);
      if(cels[a][b]==cels[c][d]){
        add(a,b,0,dp[i][j]);
        add(c,d,1,dp[i][j]);
      }
    }
    printf("\n");
  }
  printf("%i\n",dp[n-1][0]);
  return 0;
}