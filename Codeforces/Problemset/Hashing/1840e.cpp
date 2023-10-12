#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
using C=char;
const I N=2e5;
const Lli BAS=(1ll<<17)-1;
const Lli MOD=(1ll<<31)-1;
S strs[2];
Lli hshs[2];
queue<tuple<I,Lli,Lli>>ques;
Lli pows[N+1];
I n;
Lli rem(I i,C c){
  return(MOD-pows[n-1-i]*c%MOD)%MOD;
}
Lli add(I i,C c){
  return pows[n-1-i]*c%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  pows[0]=1;
  for(I i=1;i<=N;i++)pows[i]=pows[i-1]*BAS%MOD;
  I t;cin>>t;
  while(t--){
    cin>>strs[0];
    cin>>strs[1];
    n=strs[0].size();
    for(I i=0;i<2;i++){
      hshs[i]=0;
      for(I j=0;j<n;j++)hshs[i]=(hshs[i]*BAS+strs[i][j])%MOD;
    }
    I t,q;cin>>t>>q;
    while(ques.size())ques.pop();
    for(I i=0;i<q;i++){
      if(ques.size()&&get<0>(ques.front())==i){
        auto[tim,add1,add2]=ques.front();ques.pop();
        (hshs[0]+=add1)%=MOD;
        (hshs[1]+=add2)%=MOD;
      }
      I x;cin>>x;
      if(x==1){
        I pos;cin>>pos,pos--;
        ques.push({i+t,add(pos,strs[0][pos]),add(pos,strs[1][pos])});
        (hshs[0]+=rem(pos,strs[0][pos]))%=MOD;
        (hshs[1]+=rem(pos,strs[1][pos]))%=MOD;
      }
      if(x==2){
        I frm1,pos1,frm2,pos2;cin>>frm1>>pos1>>frm2>>pos2,frm1--,pos1--,frm2--,pos2--;
        (hshs[frm1]+=rem(pos1,strs[frm1][pos1]))%=MOD;
        (hshs[frm2]+=rem(pos2,strs[frm2][pos2]))%=MOD;
        (hshs[frm1]+=add(pos1,strs[frm2][pos2]))%=MOD;
        (hshs[frm2]+=add(pos2,strs[frm1][pos1]))%=MOD;
        swap(strs[frm1][pos1],strs[frm2][pos2]);
      }
      if(x==3){
        printf("%s\n",hshs[0]==hshs[1]?"YES":"NO");
      }
    }
  }
}