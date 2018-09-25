#/bin/bash!
echo '' > time.txt
sum=0.0
for i in {1..50} 
do
  sleep 0.5
  partial=$(./client localhost 4 3 | sed -n 2p) 
  sleep 1
  echo $partial >> time.txt
  sum=`echo "$partial + $sum" | bc`
  echo $sum
done

echo '---------------------' >> time.txt
echo "0$sum" | bc >> time.txt