BEGIN {
 FS = "[\[\:\"\/]"
}
$1 ~ 10 && $2 ~ Oct && $3 ~ 2006
{ sum[$15] += 1; count += 1; }

END { 
  for(i in sum) {
     print i, "-", sum[i], "-", sum[i]*100/count, "%" 
# Вывод дат, байтов и процентов. 
  } 
}
