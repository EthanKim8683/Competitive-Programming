#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I M=50;
I b_arr[M];
I ress[M];
I cnts1[M],cnts2[26];
I cnvs[M];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    S s;cin>>s;
    I m;cin>>m;
    for(I i=0;i<m;i++)cin>>b_arr[i];
    fill_n(ress,m,-1);
    fill_n(cnts1,m,0);
    fill_n(cnts2,26,0);
    I cnt=0,tot=0,len=0;
    while(cnt<m){
      I cnt1=cnt,cnt2=0;
      I tot1=tot,tot2=0;
      for(I i=0;i<m;i++){
        cnt1-=ress[i]!=-1;
        cnt2+=ress[i]!=-1;
        if(ress[i]==-1&&tot1+tot2==b_arr[i])ress[i]=len,cnt++,tot+=i;
        tot1-=cnt1;
        tot2+=cnt2;
      }
      len++;
    }
    for(I i=0;i<m;i++)cnts1[ress[i]]++;
    for(auto c:s)cnts2[c-'a']++;
    for(I i=0,j=26-1;i<len;i++,j--){
      while(cnts2[j]<cnts1[i])j--;
      cnvs[i]=j;
    }
    S res="";
    for(I i=0;i<m;i++)res+=cnvs[ress[i]]+'a';
    printf("%s\n",res.c_str());
  }
}