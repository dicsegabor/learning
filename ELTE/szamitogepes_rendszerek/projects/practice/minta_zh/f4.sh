#!/bin/bash

for i in $(find -type f -iname '*.sh'); do
    if [ $(cat $i | head -n1 | tr -s ' ' ' ') != "#!/bin/bash" ]; then
        echo $i fájlt módosítani kell
        sed -i '1s/.*/#!\/bin\/bash\n&/' $i
    fi
done
