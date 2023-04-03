#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=2e5;

I rigs[10];
I ps[10][N+1];
I movs[10];

I rng(I i,I l,I r){
  return max(ps[i][r]-ps[i][l],0);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    I n=s.size();
    fill_n(movs,10,0),fill_n(rigs,10,0);
    for(I i=0;i<10;i++)for(I j=0;j<=n;j++)ps[i][j]=0;
    for(I i=0;i<n;i++)rigs[s[i]-'0']=i;
    for(I i=0;i<n;i++)ps[s[i]-'0'][i+1]=1;
    for(I i=0;i<10;i++)for(I j=0;j<n;j++)ps[i][j+1]+=ps[i][j];
    S res="";
    I rig=0;
    for(I i=0;i<10;i++){
      movs[min(i+1,9)]+=rng(i,0,rig);
      I cur=rng(i,rig,n)+movs[i];
      for(I j=0;j<cur;j++)res+=to_string(i);
      rig=max(rig,rigs[i]);
    }
    printf("%s\n",res.c_str());
  }
}