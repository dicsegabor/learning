

while read line <&3; do
    # read & use stdin normally inside the loop
    read input
    echo "$input"
done 3<notify-finished