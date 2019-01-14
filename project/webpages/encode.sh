#!/bin/bash
foo=$(cat $1);
file_letters=
for (( i=0; i<${#foo}; i++ )); do
	letter_code=`xxd -pu <<<${foo:$i:1}`
	file_letters="$file_letters, 0x${letter_code:0:2}"
done
echo $file_letters;
