#!/bin/sh

#Checking if the file exists
INPUT_FILE=$1
if [ ! -f "$INPUT_FILE" ]; then
    echo ERROR: The given file \'$INPUT_FILE\' does not exist!
    exit 1
fi

# Accumulator variables
declare -a NON_VIOLENT
SECURITY=0
MOST_CRIME=0
declare -a WORST_PLACES

# Read the file line by line
while IFS= read -r LINE; do

    # Split the line into an array
    IFS=',' read -ra ITEMS <<<$LINE

    # Error if a given line has too few elements
    if [ ${#ITEMS[@]} -ne 4 ]; then
        echo ERROR: The given line \'${ITEMS[@]}\' does not contain the requested data!
        exit 1
    fi

    # Removing leading spaces
    for i in ${!ITEMS[@]}; do
        ITEMS[$i]=`echo ${ITEMS[$i]} | sed 's/ *$//g'`
    done

    # Searching for workplaces with 0 violent crime
    if [ ${ITEMS[2]} -eq 0 ]; then
        NON_VIOLENT+=("${ITEMS[0]}")
    fi

    # Summing the security guards
    SECURITY=$(expr $SECURITY + ${ITEMS[3]})

    # Filtering out the worst places
    if [ ${ITEMS[2]} -gt $MOST_CRIME ]; then
        MOST_CRIME=${ITEMS[2]}
        unset WORST_PLACES
    fi

    if [ ${ITEMS[2]} -eq $MOST_CRIME ]; then
        WORST_PLACES+=("${ITEMS[0]},\t${ITEMS[1]}")
    fi

done <$INPUT_FILE

# Print the names of the non violent workplaces
echo "Erőszakmentes munkahelyek:"
if [ ${#NON_VIOLENT[@]} -ne 0 ]; then
    for var in "${NON_VIOLENT[@]}"; do
        echo -e "\t- $var"
    done
else
    echo -e "\t- NINCS"
fi

# Print the sum of all security guards
echo "Biztonsági őrök összesen:"
echo -e "\t- $SECURITY"

# Print the most violent workplaces
echo "Legtöbb erőszakot jelentő munkahelyek:"
for var in "${WORST_PLACES[@]}"; do
    echo -e "\t- $var"
done
