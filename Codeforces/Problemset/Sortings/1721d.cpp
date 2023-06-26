#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
const I A=(1<<30)-1;
const I LOGA=30;
I a_arr[N];
I b_arr[N];
queue<tuple<I,I,I,I>>ques;
B vias[LOGA];
I y;
B cmp(I a,I b){
  return(a>>y&1)<(b>>y&1);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)cin>>b_arr[i];
    fill_n(vias,LOGA,1);
    ques.push({1,LOGA-1,0,n});
    while(ques.size()){
      auto[m,x,l,r]=ques.front();ques.pop();
      if(x<0||l>=r)continue;
      if(m==1){
        I cnt1=0,cnt2=r-l;
        for(I i=l;i<r;i++)cnt1+=a_arr[i]>>x&1;
        for(I i=l;i<r;i++)cnt2-=b_arr[i]>>x&1;
        vias[x]&=cnt1==cnt2;
        ques.push({2,x,l,r});
      }
      if(m==2){
        if(!vias[x]){ques.push({1,x-1,l,r});continue;}
        I cnt=0;
        for(I i=l;i<r;i++)cnt+=a_arr[i]>>x&1;
        y=x;
        sort(a_arr+l,a_arr+r,cmp);
        sort(b_arr+l,b_arr+r,cmp);
        reverse(b_arr+l,b_arr+r);
        ques.push({1,x-1,l,r-cnt});
        ques.push({1,x-1,r-cnt,r});
      }
    }
    I res=A;
    for(I i=0;i<n;i++)res&=a_arr[i]^b_arr[i];
    printf("%i\n",res);
  }
}