BEGIN {
   FS="\""
}
$1 ~ /18\/Oct\/2006/ && $4 != "-" { sum[$4] += 1; s += 1; }
END { 
  for(i in sum) {
     print i, "-", sum[i], "-", sum[i]*100/s, "%" 
  } 
}
