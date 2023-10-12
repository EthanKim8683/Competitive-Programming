n=int(input())
res,pre,i,cnts=0,0,0,{}
for a in map(int,input().split()):
  res+=i*a-pre
  if a+1 in cnts.keys():
    res+=cnts[a+1]
  if a-1 in cnts.keys():
    res-=cnts[a-1]
  pre+=a
  if a not in cnts.keys():
    cnts[a]=0
  cnts[a]+=1
  i+=1
print(res)