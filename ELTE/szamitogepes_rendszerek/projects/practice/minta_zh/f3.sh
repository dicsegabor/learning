#!/bin/bash

num=0
while [ $num -ne 1 ]
do
    clear
    echo "1) kilépés"
    echo "2) bejelentkezett felhasználók mentése"
    echo "3) dátum kiírása"
    echo -n "válasszon a menüpontok közül: "

    read num
    case $num in
        1) echo kilepes... && sleep 1 && clear ;;
        2) echo who | cut -f1 -d ' ' >users.txt ;;
        3) date "+%Y évet írunk és %m hó %d-dike van, %A" ;;
        *) echo nincs ilyen menüpont ;;
    esac

    sleep 1
done
