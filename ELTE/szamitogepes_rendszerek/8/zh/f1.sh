#!/bin/bash

append_to_files() {
    for file in $(find -type f -empty); do
        echo hello > "$file"
    done
}

num=0
while [ $num -ne 4 ]; do
    clear

    echo "1) munkakönyvtár teljes elérési útvonala"
    echo "2) a /bin könyvtár s betűvel kezdődő bejegyzéseinek száma"
    echo "3) minden munkakönyvtárbeli üres fájlhoz hozzáfűzi, hogy hello"
    echo "4) kilépés"
    echo -n "válasszon a menüpontok közül: "

    read num
    case $num in
    1) pwd ;;
    2) ls -a /bin | grep "^s.*" | wc -l ;;
    3) append_to_files ;;
    *) ;;
    esac

    sleep 1
done

clear

