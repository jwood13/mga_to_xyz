#!/bin/bash
for f in $(ls mga_movie.*[0-9])
do
    if [ ! -f ${f}.xyz ]; then
        xyzconversion.out $f &
    fi
    echo -n -e "\r$f          "
done
echo 
