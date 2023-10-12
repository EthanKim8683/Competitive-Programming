#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
const I N=2e5;
vector<pair<I,I>>rngs;
vector<I>reps[3];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I a,b,c,d;cin>>a>>b>>c>>d;
    S s;cin>>s;
    I n=s.size();
    I cnt1=0,cnt2=0,cnt3=0,cnt4=0;
    for(I i=0;i<n;i++){
      if(s[i]=='A')cnt1++;
      if(s[i]=='B')cnt2++;
    }
    for(I i=0;i+1<n;i++){
      if(s[i]!='A'||s[i+1]!='B')continue;
      cnt1--,cnt2--,cnt3++;
    }
    rngs.clear();
    for(I i=0;i<3;i++)reps[i].clear();
    I j=-1;
    for(I i=0;i<n;){
      if(s[i]=='B'&&i+1<n&&s[i+1]=='A'){
        if(j==-1)j=i;
        i+=2;
      }else{
        if(j!=-1)rngs.push_back({j,i}),j=-1;
        i++;
      }
    }
    if(j!=-1)rngs.push_back({j,n});
    for(auto[l,r]:rngs){
      I cst=0;
      if(l-1>=0&&s[l-1]=='A')cst++;
      if(r<n&&s[r]=='B')cst++;
      reps[cst].push_back((r-l)/2);
    }
    sort(reps[0].begin(),reps[0].end());
    sort(reps[2].begin(),reps[2].end(),greater<I>());
    for(auto cnt:reps[0]){
      I dif=min(cnt,d-cnt4);
      if(dif==0)break;
      if(dif==cnt){
        cnt3-=dif-1;
        cnt1--,cnt2--;
        cnt4+=dif;
      }else{
        cnt3-=dif;
        cnt4+=dif;
      }
    }
    for(auto cnt:reps[1]){
      I dif=min(cnt,d-cnt4);
      if(dif==0)break;
      cnt3-=dif,cnt4+=dif;
    }
    for(auto cnt:reps[2]){
      I dif=min(cnt,d-cnt4);
      if(dif==0)break;
      cnt1++,cnt2++,cnt3-=dif+1,cnt4+=dif;
    }
    I dif1=a-cnt1,dif2=b-cnt2;
    if(cnt4!=d){printf("NO\n");continue;}
    if(dif1!=dif2){printf("NO\n");continue;}
    if(dif1<0){printf("NO\n");continue;}
    if(cnt3-dif1!=c){printf("NO\n");continue;}
    printf("YES\n");
  }
}