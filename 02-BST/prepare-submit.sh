#!/bin/bash

BASE_DIR="$(basename $( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd ))"
ASSIGN_NUM=$(echo $(echo $BASE_DIR | cut -f1 -d-) | sed 's/^0*//')
TAR=assign${ASSIGN_NUM}.tar.gz
FILES=("./include/BST.hpp")

echo "[*] Remove tar file..."
rm -f $TAR || echo ""

echo "[*] Compress files..."
tar cvzf $TAR ${FILES[@]} || echo ""

RESULT=$(tar -tf $TAR | tr " " "\n")
i=0
for FILE in $RESULT; do
    if [[ ! " ${FILES[@]} " =~ " ${FILE} " ]]; then
        echo "[*] Error: Your tar file seems to be broken. Please check."
    fi
    i+=1
done

if [ ${#FILES[@]} -ne $i ]; then
    echo "[*] Error: Your tar file seems to be broken. Please check."
fi

echo "[*] Successfully Compressed!"
echo "[*] Done! You are ready to submit"
