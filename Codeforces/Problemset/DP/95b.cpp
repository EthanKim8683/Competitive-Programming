#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I M=100001;
pair<I,I>dp[M+1][2];
I bins[M];
vector<pair<I,I>>chks;
vector<I>ress;
void rem(){
  if(!chks.size())return;
  if(!--chks.back().first)chks.pop_back();
}
void add(I len,I val){
  if(!chks.size()||chks.back().second!=val)chks.push_back({len,val});
  else chks.back().first+=len;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(M+1)*2,pair<I,I>{-1,-1});
  S n;cin>>n;
  I m=n.size();
  if(m%2){
    for(I i=0;i<(m+1)/2;i++)printf("4");
    for(I i=0;i<(m+1)/2;i++)printf("7");
    exit(0);
  }
  dp[0][0]={-1,2};
  dp[0][1]={-1,0};
  for(I i=0;i<m;i++){
    if(dp[i][1].second!=-1){
      dp[i+1][1]={1,0};
    }
    if(dp[i][0].second!=-1){
      if(n[i]<'7')dp[i+1][1]={0,1};
      if(n[i]=='7')dp[i+1][0]={0,1};
      if(n[i]<'4')dp[i+1][1]={0,0};
      if(n[i]=='4')dp[i+1][0]={0,0};
    }
  }
  I j=-1;
  if(dp[m][1].second!=-1)j=1;
  if(dp[m][0].second!=-1)j=0;
  for(I i=m;i>=0;i--){
    auto[x,y]=dp[i][j];
    bins[i]=y,j=x;
  }
  I cnt=0,tot=0;
  for(I i=0;i<=m;){
    if(bins[i]==2){i++;continue;}
    I len=0,bin=bins[i];
    while(i<=m&&bins[i]==bin)i++,len++;
    chks.push_back({len,bin});
    if(bin)cnt+=len;
    tot+=len;
  }
  while(cnt>tot-cnt){
    if(chks.back().second==1)chks.push_back({0,0});
    auto[len0,val0]=chks.back();chks.pop_back();
    auto[len1,val1]=chks.back();chks.pop_back();
    if(chks.size())rem();
    else tot++;
    add(1,1);
    add(len0+len1,0);
    cnt+=1-len1;
  }
  if(tot%2){
    for(I i=0;i<(tot+1)/2;i++)printf("4");
    for(I i=0;i<(tot+1)/2;i++)printf("7");
    exit(0);
  }
  for(auto[len,val]:chks)for(I i=0;i<len;i++)ress.push_back(val);
  for(I i=ress.size()-1;i>=0&&cnt<tot-cnt;i--){
    if(ress[i])continue;
    ress[i]=1,cnt++;
  }
  for(auto res:ress)printf("%i",res?7:4);
}