#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=1e4;
const I MAX=1e9;
I cnts[10];
I reps[10];
I csts[10];
S trns[10];
vector<S>cans;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  S s;cin>>s;
  for(I i=0;i<n;i++)cnts[s[i]-'0']++;
  for(I i=0;i<=9;i++){
    I rem=max(k-cnts[i],0),cst=0;
    for(I j=1;j<10;j++){
      if(i+j<=9){
        I dif=min(rem,cnts[i+j]);
        rem-=dif,cst+=j*dif,reps[i+j]=dif;
      }
      if(i-j>=0){
        I dif=min(rem,cnts[i-j]);
        rem-=dif,cst+=j*dif,reps[i-j]=dif;
      }
    }
    S t=s;
    for(I j=0;j<10;j++){
      if(j>i)for(I k=0;k<n;k++){
        if(reps[j]==0)break;
        if(t[k]-'0'!=j)continue;
        t[k]=i+'0',reps[j]--;
      }
      if(j<i)for(I k=n-1;k>=0;k--){
        if(reps[j]==0)break;
        if(t[k]-'0'!=j)continue;
        t[k]=i+'0',reps[j]--;
      }
    }
    csts[i]=cst;
    trns[i]=t;
  }
  I low=*min_element(csts,csts+10);
  for(I i=0;i<10;i++){
    if(csts[i]!=low)continue;
    cans.push_back(trns[i]);
  }
  sort(cans.begin(),cans.end());
  printf("%i\n",low);
  printf("%s\n",cans.front().c_str());
}