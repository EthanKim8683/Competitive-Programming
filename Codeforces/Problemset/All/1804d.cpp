#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using B=bool;
const I M=5e5;
C wins[M+1];
vector<tuple<C,I,I>>rngs;
vector<I>twos;
B viss[M];
I cnts[2];
B cmp(I a,I b){
  return wins[a]+wins[a+1]<wins[b]+wins[b+1];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  I res1=0,res2=0;
  while(n--){
    cin>>wins;
    cnts[0]=cnts[1]=0;
    for(I i=0;i<m;i++)cnts[wins[i]-'0']++;
    I cnt=0;
    for(I i=0;i+1<m;i++){
      I a=wins[i],b=wins[i+1];
      if(a!='1'||b!='1')continue;
      cnt++,i++;
    }
    res1+=cnts[1]-2*cnt;
    I dif=max(cnt-m/4,0);
    cnt-=dif,res1+=cnt+dif*2;
    C pre=wins[0];I l=0;
    rngs.clear();
    for(I i=1;i<m;i++){
      if(wins[i]!=pre)rngs.push_back({pre,l,i}),l=i;
      pre=wins[i];
    }
    rngs.push_back({pre,l,m});
    twos.clear();
    I upp=0;
    for(auto[c,l,r]:rngs){
      if(c=='1')continue;
      if(l>0)l--;
      if(r<m)r++;
      l=max(l,upp);
      r=l+(r-l)/2*2;
      for(I i=l;i<r;i+=2)twos.push_back(i);
      upp=max(upp,r);
    }
    sort(twos.begin(),twos.end(),cmp);
    while(twos.size()>m/4)twos.pop_back();
    fill_n(viss,m,0);
    for(auto i:twos)viss[i]=viss[i+1]=1;
    for(I i=0;i+1<m&&twos.size()<m/4;i++){
      if(viss[i]||viss[i+1])continue;
      twos.push_back(i);
      viss[i]=viss[i+1]=1;
    }
    for(auto i:twos)res2+=wins[i]=='1'||wins[i+1]=='1';
    for(I i=0;i<m;i++)if(!viss[i])res2+=wins[i]=='1';
  }
  printf("%i %i\n",res1,res2);
}