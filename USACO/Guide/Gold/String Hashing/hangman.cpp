#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
using I128=__int128;
using B=bool;
const I T=10;
const I N=3e4;
const I K=3e4;
const I M=1200;
const Lli BAS=4347;
const Lli MOD=(1ll<<61)-1;
S wrds[N];
Lli pows[K+1];
B ress[N];
vector<pair<Lli,I>>accs;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  pows[0]=1;
  for(I i=1;i<=K;i++)pows[i]=(I128)pows[i-1]*BAS%MOD;
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>wrds[i];
    fill_n(ress,n,0);
    if(n<=M){
      for(I i=0;i<n;i++)for(I j=0;j<i;j++){
        I cnt=0;
        for(I l=0;l<k;l++)cnt+=wrds[i][l]!=wrds[j][l];
        if(cnt<=2)ress[i]=ress[j]=1;
      }
    }else{
      accs.clear();
      for(I i=0;i<n;i++){
        Lli hsh=0;
        for(I j=0;j<k;j++)hsh=((I128)hsh*BAS+wrds[i][j])%MOD;
        for(I j=0;j<k;j++)for(I l=0;l<j;l++)accs.push_back({((hsh+(I128)(1-wrds[i][j])*pows[k-1-j]+(I128)(1-wrds[i][l])*pows[k-1-l])%MOD+MOD)%MOD,i});
      }
      sort(accs.begin(),accs.end());
      for(I i=1;i<accs.size();i++){
        auto[hsh1,j]=accs[i-1];auto[hsh2,k]=accs[i];
        if(hsh1==hsh2)ress[j]=ress[k]=1;
      }
    }
    for(I i=0;i<n;i++)printf("%i",ress[i]);
    printf("\n");
  }
}