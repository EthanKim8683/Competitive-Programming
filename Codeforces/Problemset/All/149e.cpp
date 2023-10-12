#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
const I N=1e5;
const I M=100;
const I K=1000;
S p_arr[M];
I lcps[N+K+1];
I pres1[M][N],sufs1[M][N];
I pres2[M][N],sufs2[M][N];
void zfn(S s){
  I n=s.size();
  fill_n(lcps,n,0);
  for(I l=0,r=0,i=1;i<n;i++){
    if(i<r)lcps[i]=min(r-i,lcps[i-l]);
    while(i+lcps[i]<n&&s[lcps[i]]==s[i+lcps[i]])lcps[i]++;
    if(i+lcps[i]>r)l=i,r=i+lcps[i];
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n=s.size();
  I m;cin>>m;
  for(I i=0;i<m;i++)cin>>p_arr[i];
  S t=s;
  reverse(t.begin(),t.end());
  for(I i=0;i<m;i++){
    S p=p_arr[i];
    zfn(p+"$"+s);
    for(I j=0;j<n;j++)pres1[i][j]=lcps[j+p.size()+1];
    S q=p;
    reverse(q.begin(),q.end());
    zfn(q+"$"+t);
    for(I j=0;j<n;j++)sufs1[i][n-1-j]=lcps[j+p.size()+1];
  }
  for(I i=0;i<m;i++){
    for(I j=0;j<n;j++){
      I pre=pres1[i][j];
      if(pre>0)pres2[i][j+pre-1]=max(pres2[i][j+pre-1],pre);
    }
    for(I j=n-1;j>=0;j--){
      I suf=sufs1[i][j];
      if(suf>0)sufs2[i][j-suf+1]=max(sufs2[i][j-suf+1],suf);
    }
    for(I j=n-1;j>0;j--)pres2[i][j-1]=max(pres2[i][j-1],pres2[i][j]-1);
    for(I j=0;j<n-1;j++)sufs2[i][j+1]=max(sufs2[i][j+1],sufs2[i][j]-1);
  }
  I res=0;
  for(I i=0;i<m;i++)if(p_arr[i].size()>1){
    B fnd=0;
    for(I j=n-1;j>0;j--)sufs2[i][j-1]=max(sufs2[i][j-1],sufs2[i][j]);
    for(I j=0;j+1<n;j++)fnd|=pres2[i][j]+sufs2[i][j+1]>=p_arr[i].size();
    res+=fnd;
  }
  printf("%i\n",res);
}
/*
we can use the z-function to find the longest common prefix of each beautiful
word starting at each index i

similarly, we can z-function again to find the longest common suffix of each
beautiful word ending at each index i

now, we can check for each beautiful word if it's possible to pair a prefix
and suffix to produce the entire word
*/