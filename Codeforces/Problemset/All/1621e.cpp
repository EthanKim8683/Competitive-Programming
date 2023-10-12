#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1e5;
const I M=1e5;
I a_arr[N];
vector<I>b_arr[M];
I aves[M];
I inds[M];
I invs[M];
B segs[3][2*M];
I m;
void asn(I t,I i,B val){
  segs[t][i+m]=val;
}
void bld(){
  for(I t=0;t<3;t++)for(I i=m-1;i>0;i--)segs[t][i]=segs[t][i<<1]&segs[t][i<<1|1];
}
B qry(I t,I l,I r){
  B res=1;
  for(l+=m,r+=m;l<r;l>>=1,r>>=1){
    if(l&1)res&=segs[t][l++];
    if(r&1)res&=segs[t][--r];
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n,greater<I>());
    reverse(a_arr,a_arr+m);
    for(I i=0;i<m;i++)b_arr[i].clear();
    for(I i=0;i<m;i++){
      I k;cin>>k;
      b_arr[i].resize(k);
      for(I j=0;j<k;j++)cin>>b_arr[i][j];
      Lli sum=0;
      for(I j=0;j<k;j++)sum+=b_arr[i][j];
      aves[i]=(sum+k-1)/k;
    }
    iota(inds,inds+m,0);
    sort(inds,inds+m,[&](I a,I b){
      return aves[a]<aves[b];
    });
    for(I i=0;i<m;i++)invs[inds[i]]=i;
    for(I i=0;i<m;i++){
      I j=inds[i];
      if(i-1>=0)asn(0,i,a_arr[i-1]>=aves[j]);
      if(i+1<m)asn(1,i,a_arr[i+1]>=aves[j]);
      asn(2,i,a_arr[i]>=aves[j]);
    }
    bld();
    for(I i=0;i<m;i++){
      I k=b_arr[i].size(),l=invs[i];
      Lli sum=0;
      for(I j=0;j<k;j++)sum+=b_arr[i][j];
      for(I j=0;j<k;j++){
        Lli ref=(sum-b_arr[i][j]+k-2)/(k-1);
        if(ref<aves[i]){
          I o=upper_bound(inds,inds+m,ref,[&](I a,I b){
            return a<aves[b];
          })-inds;
          printf("%i",qry(1,o,l)&qry(2,0,o)&qry(2,l+1,m)&a_arr[o]>=ref);
        }
        if(ref>aves[i]){
          I o=upper_bound(inds,inds+m,ref,[&](I a,I b){
            return a<aves[b];
          })-inds;
          printf("%i",qry(0,l+1,o)&qry(2,0,l)&qry(2,o,m)&a_arr[o-1]>=ref);
        }
        if(ref==aves[i])printf("%i",qry(2,0,m));
      }
    }
    printf("\n");
  }
}
/*
we can assign teachers greedily if we sort the teachers and students in
non-increasing order of age and average age, respectively

then, we assign the oldest teacher with the oldest group (on average), the
second oldest teacher to the second oldest group (on average), and so on

this works because if a younger group requires an older teacher, so does
an older group, meaning it would not be possible to start lessons

meanwhile, if a group's average increases as a result of a refusal, all
groups displaced after re-sorting will recieve a teacher with age one
after their original

we can check if this results in lessons being impossible by storing for all
groups whether, if displaced in such a way, would lessons become impossible

if a group's average decreases as a result of a refusal, all groups displaced
after re-sorting will recieve a teacher with age one before their original

similarly, we can store if lessons become possible after such a displacement
*/