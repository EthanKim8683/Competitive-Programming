#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=17;

vector<I>unvs[2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    unvs[0].clear();
    unvs[1].clear();
    for(I i=1;i<=(1<<n);i++)unvs[0].push_back(i);
    I j=0;
    while(unvs[j].size()>2){
      while(unvs[j].size()){
        I a=unvs[j].back();
        unvs[j].pop_back();
        I b=unvs[j].back();
        unvs[j].pop_back();
        I c=unvs[j].back();
        unvs[j].pop_back();
        I d=unvs[j].back();
        unvs[j].pop_back();
        printf("? %i %i\n",a,c);
        fflush(stdout);
        I r;cin>>r;
        if(r==1)b=a;
        if(r==2)d=c;
        printf("? %i %i\n",b,d);
        fflush(stdout);
        cin>>r;
        unvs[!j].push_back(r==1?b:d);
      }
      j^=1;
    }
    if(unvs[j].size()==2){
      I a=unvs[j][0],b=unvs[j][1];
      printf("? %i %i\n",a,b);
      fflush(stdout);
      I r;cin>>r;
      printf("! %i\n",r==1?a:b);
      fflush(stdout);
    }else{
      printf("! %i\n",unvs[j][0]);
      fflush(stdout);
    }
  }
  return 0;
}