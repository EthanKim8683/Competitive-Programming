#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=1e5;

I ress[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    I x;cin>>x;
    I n=s.size();
    fill_n(ress,n,-1);
    B vld=1;
    for(I i=0;i<n;i++){
      I c=s[i]=='1';
      if(i-x <0&&i+x>=n&&                              c==0);
      if(i-x <0&&i+x>=n&&                              c==1)vld=0;
      if(i-x <0&&i+x <n&&               ress[i+x]==-1&&c==0)ress[i+x]=0;
      if(i-x <0&&i+x <n&&               ress[i+x]==-1&&c==1)ress[i+x]=1;
      if(i-x <0&&i+x <n&&               ress[i+x]== 0&&c==0);
      if(i-x <0&&i+x <n&&               ress[i+x]== 0&&c==1)vld=0;
      if(i-x <0&&i+x <n&&               ress[i+x]== 1&&c==0)vld=0;
      if(i-x <0&&i+x <n&&               ress[i+x]== 1&&c==1);
      if(i-x>=0&&i+x>=n&&ress[i-x]==-1&&               c==0)ress[i-x]=0;
      if(i-x>=0&&i+x>=n&&ress[i-x]==-1&&               c==1)ress[i-x]=1;
      if(i-x>=0&&i+x>=n&&ress[i-x]== 0&&               c==0);
      if(i-x>=0&&i+x>=n&&ress[i-x]== 0&&               c==1)vld=0;
      if(i-x>=0&&i+x>=n&&ress[i-x]== 1&&               c==0)vld=0;
      if(i-x>=0&&i+x>=n&&ress[i-x]== 1&&               c==1);
      if(i-x>=0&&i+x <n&&ress[i-x]==-1&&ress[i+x]==-1&&c==0)ress[i-x]=0,ress[i+x]=0;
      if(i-x>=0&&i+x <n&&ress[i-x]==-1&&ress[i+x]==-1&&c==1)ress[i-x]=1;
      if(i-x>=0&&i+x <n&&ress[i-x]==-1&&ress[i+x]== 0&&c==0)ress[i-x]=0;
      if(i-x>=0&&i+x <n&&ress[i-x]==-1&&ress[i+x]== 0&&c==1)ress[i-x]=1;
      if(i-x>=0&&i+x <n&&ress[i-x]==-1&&ress[i+x]== 1&&c==0)vld=0;
      if(i-x>=0&&i+x <n&&ress[i-x]==-1&&ress[i+x]== 1&&c==1);
      if(i-x>=0&&i+x <n&&ress[i-x]== 0&&ress[i+x]==-1&&c==0)ress[i+x]=0;
      if(i-x>=0&&i+x <n&&ress[i-x]== 0&&ress[i+x]==-1&&c==1)ress[i+x]=1;
      if(i-x>=0&&i+x <n&&ress[i-x]== 0&&ress[i+x]== 0&&c==0);
      if(i-x>=0&&i+x <n&&ress[i-x]== 0&&ress[i+x]== 0&&c==1)vld=0;
      if(i-x>=0&&i+x <n&&ress[i-x]== 0&&ress[i+x]== 1&&c==0)vld=0;
      if(i-x>=0&&i+x <n&&ress[i-x]== 0&&ress[i+x]== 1&&c==1);
      if(i-x>=0&&i+x <n&&ress[i-x]== 1&&ress[i+x]==-1&&c==0)vld=0;
      if(i-x>=0&&i+x <n&&ress[i-x]== 1&&ress[i+x]==-1&&c==1);
      if(i-x>=0&&i+x <n&&ress[i-x]== 1&&ress[i+x]== 0&&c==0)vld=0;
      if(i-x>=0&&i+x <n&&ress[i-x]== 1&&ress[i+x]== 0&&c==1);
      if(i-x>=0&&i+x <n&&ress[i-x]== 1&&ress[i+x]== 1&&c==0)vld=0;
      if(i-x>=0&&i+x <n&&ress[i-x]== 1&&ress[i+x]== 1&&c==1);
    }
    if(!vld){printf("-1\n");continue;}
    for(I i=0;i<n;i++)printf("%i",ress[i]==1);
    printf("\n");
  }
}