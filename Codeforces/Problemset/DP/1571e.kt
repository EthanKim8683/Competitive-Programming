val MAX=1e9.toInt()

fun chk(x:Int):Boolean{
  if(x==0b0101)return true
  if(x==0b0011)return true
  return false
}

fun toi(x:Char):Int{
  if(x=='(')return 0;
  return 1;
}

fun main(){
  val t=readLine()!!.toInt()
  for(x in 1..t){
    val n=readLine()!!.toInt()
    val s=readLine()!!
    val a=readLine()!!
    val dp=Array(n-3,{i->Array(1 shl 4,{j->MAX})})
    for(i in 0..(1 shl 4)-1){
      if(a[0]=='1'&&!chk(i))continue
      var cst=0
      for(j in 0..3)if(((i shr (3-j)) and 1)!=toi(s[j]))cst++
      dp[0][i]=cst
    }
    for(i in 0..n-5)for(j in 0..(1 shl 4)-1){
      val c=toi(s[i+4])
      val x=((j shl 1) or c) and 0b1111
      val y=((j shl 1) or (1-c)) and 0b1111
      if(a[i+1]=='0'||chk(x))dp[i+1][x]=Math.min(dp[i+1][x],dp[i][j])
      if(a[i+1]=='0'||chk(y))dp[i+1][y]=Math.min(dp[i+1][y],dp[i][j]+1)
    }
    var res=MAX
    for(i in 0..(1 shl 4)-1)res=Math.min(res,dp[n-4][i])
    if(res==MAX)println("-1")
    else println(res)
  }
}