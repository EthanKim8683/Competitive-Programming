#include<bits/stdc++.h>
using namespace std;
using I=int;
const I LOGA=17;
const I A=1<<LOGA;
I a_arr[A];
I segs[2][2*A];
I res;
void upd(I i,I j,I val){
  for(segs[i][j+=A]+=val;j>>=1;)segs[i][j]=segs[i][j<<1]+segs[i][j<<1|1];
}
void dfs(I i,I j,I k=LOGA-1){
  if(segs[1][i]==0&&segs[0][j]==0)return;
  if(segs[1][i<<1]!=segs[0][j<<1]||segs[1][i<<1|1]!=segs[0][j<<1|1]){
    res|=1<<k;
    if(k>0)dfs(i<<1|1,j<<1,k-1),dfs(i<<1,j<<1|1,k-1);
  }else{
    if(k>0)dfs(i<<1,j<<1,k-1),dfs(i<<1|1,j<<1|1,k-1);
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I l,r;cin>>l>>r,r++;
    for(I i=0;i<r-l;i++)cin>>a_arr[i];
    for(I i=0;i<r-l;i++)upd(0,i+l,1),upd(1,a_arr[i],1);
    res=0,dfs(1,1);
    printf("%i\n",res);
    for(I i=0;i<r-l;i++)upd(0,i+l,-1),upd(1,a_arr[i],-1);
  }
}
/*
since an xor operation effectively swaps segments of the original array, we
can determine when swaps are needed by checking the counts on the segments
to be swapped when xor-ing a given bit

if the counts are not equal to what they should be in the original array,
the bit is positive

if we check the bits in decreasing order of significance, this process should
always yield the correct x because, if two counts are equal, even if they
correspond to different parts of the original array, they can be made to
equal its original counterparts

this is because they are both contiguous and, if both counts are positive,
they must meet in the middle, meaning they are symmetrical and otherwise,
there are no numbers to fix
*/