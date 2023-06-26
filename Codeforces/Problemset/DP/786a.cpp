#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using S=string;
const I N=7000;
const I K=N-1;
I k_arr[2];
I s_arr[2][K];
I wins[2][N];
I ress[2][N];
void win(I,I);
void los(I,I);
I n;
void win(I i,I j){
  if(j==0||ress[i][j]!=2)return;
  ress[i][j]=1;
  for(I k=0;k<k_arr[!i];k++){
    I l=(j-s_arr[!i][k]+n)%n;
    if(++wins[!i][l]==k_arr[!i])los(!i,l);
  }
}
void los(I i,I j){
  if(j==0||ress[i][j]!=2)return;
  ress[i][j]=0;
  for(I k=0;k<k_arr[!i];k++){
    I l=(j-s_arr[!i][k]+n)%n;
    win(!i,l);
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&ress[0][0],&ress[0][0]+2*N,2);
  cin>>n;
  cin>>k_arr[0];
  for(I i=0;i<k_arr[0];i++)cin>>s_arr[0][i];
  cin>>k_arr[1];
  for(I i=0;i<k_arr[1];i++)cin>>s_arr[1][i];
  for(I i=0;i<2;i++)sort(s_arr[i],s_arr[i]+k_arr[i]);
  for(I i=0;i<2;i++)for(I j=0;j<n;j++)if(binary_search(s_arr[i],s_arr[i]+k_arr[i],n-j))win(i,j);
  for(I i=0;i<2;i++){
    for(I j=1;j<n;j++)printf("%s ",(S[]){"Lose","Win","Loop"}[ress[i][j]].c_str());
    printf("\n");
  }
}