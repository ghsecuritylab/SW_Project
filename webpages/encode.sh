#!/bin/bash
NL=$'\n'
foo=$(find -maxdepth 1 -type f -exec basename {} \;);
for filename in $foo
do
	if [ "$filename" = "encode.sh" ]; then
		continue
	fi
	if [ "${filename#*.}" != "h" ]; then
		file_content=$(cat $filename)
		file_letters=
		i=0
		for (( i=0; i<${#file_content}; i++ )); do
			if [ $((i%15)) -eq 0 ]; then
				file_letters=${file_letters}${NL}
			fi
			letter_code=`xxd -pu <<<"${file_content:$i:1}"`
			file_letters="${file_letters}0x${letter_code:0:2}, "
		done
		file_letters=${file_letters#${NL}}
		file_letters=${file_letters%, }
		echo "unsigned char ${filename%.*}_h[] = {" > "${filename%.*}_h.h"
		echo "$file_letters" >> "${filename%.*}_h.h"
		echo "};" >> "${filename%.*}_h.h"
		echo "unsigned int ${filename%.*}_h_length = $i;" >> "${filename%.*}_h.h"
		echo >> "${filename%.*}_h.h"
	fi
done

