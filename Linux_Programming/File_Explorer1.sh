#!/bin/bash

print_frame() {
	tput cup 0 0
	printf "[46m File System"
	printf " %.0s" {1..71}
	printf "\n[47m\u250c"
	printf "\u2500%.0s" {1..40}
	printf "\u2500"
	printf "\u2500%.0s" {1..40}
	printf "\u2510\n\u2502"
	printf " %.0s" {1..81}
	printf "\u2502\n\u251c"
	printf "\u2500%.0s" {1..40}
	printf "\u252c"
	printf "\u2500%.0s" {1..40}
	printf "\u2524\n"

	for i in {4..24}; do
		printf "\u2502"
		printf " %.0s" {1..40}
		printf "\u2502"
		printf " %.0s" {1..40}
		printf "\u2502\n"
	done

	printf "[47m\u251c"
	printf "\u2500%.0s" {1..40}
	printf "\u2534"
	printf "\u2500%.0s" {1..40}
	printf "\u2524\n\u2502"
	printf " %.0s" {1..81}
	printf "\u2502\n\u2514"
	printf "\u2500%.0s" {1..81}
	printf "\u2518\n"
}

print_line() {
	array=($(ls -al))

	idx=$((9*$1+10))
	name=$(echo ${array[$idx]})

	idx=$((9*$1+2))
	perm=$(echo ${array[$idx]})

	idx=$((9*$1+6))
	size=$(echo ${array[$idx]})

	
	tput cup $(($1+4)) 1
	if [ $(($2)) == 1 ]; then
		printf "[41m"
	else
		printf "[47m"
	fi
	printf " %.0s" {1..40}

	tput cup $(($1+4)) 2
	if [ -d $name ]; then
		printf "[34m%-15s %-15s %-5s[30m" $name $perm $size
	elif [ -x $name ]; then
		printf "[32m%-15s %-15s %-5s[30m" $name $perm $size
	else
		printf "[30m%-15s %-15s %-5s[30m" $name $perm $size
	fi
	printf "[47m"

	tput cup 28 0
}

print_pwd_info() {
	tput cup 2 2
	printf "Current path:$(pwd)"
	tput cup 28 0
}

print_dir_info() {
	DIR_SIZE=0
	FILE_SIZE=0
	TOTAL_BYTE=`get_total_size`

	for file in `ls`; do 	
		if [ -d ${file} ]; then	
			DIR_SIZE=$((${DIR_SIZE}+1))
		else 
			FILE_SIZE=$((${FILE_SIZE}+1))
		fi
	done

	TOTAL_SIZE=`convert_size ${TOTAL_BYTE}`

	tput cup 26 2
	printf "Directory: ${DIR_SIZE}"
	tput cup 26 22
	printf "File: ${FILE_SIZE}"
	tput cup 26 45
	printf "Current Diretory Size: ${TOTAL_SIZE}"
	tput cup 28 0
}

get_total_size() {
	ls -l | awk '{ total += $5 }; END { print total }'
}

convert_size() {
	#"size"
	FILESIZE=$1

	if [ ${FILESIZE} -lt 1024 ]; then
		echo "${FILESIZE}B"
		return
	else
		FSIZE_TMP=`echo "${FILESIZE} / 1024" | bc`
		FILESIZE=`echo "scale=2; ${FILESIZE} / 1024" | bc`	
		if [ ${FSIZE_TMP} -lt 1024 ]; then
			echo "${FILESIZE}K"
			return
		else
			FSIZE_TMP=`echo "${FILESIZE} / 1024" | bc`
			FILESIZE=`echo "scale=2; ${FILESIZE} / 1024" | bc`	
			if [ ${FSIZE_TMP} -lt 1024 ]; then
				echo "${FILESIZE}M"
				return
			else
				FILESIZE=`echo "scale=2; ${FILESIZE} / 1024" | bc`
				echo "${FILESIZE}G"
				return
			fi
		fi
	fi
}



print_tree() {
	array1=($(ls -al))
	idx1=$((9*$1+10))
	name1=$(echo ${array1[$idx1]})

	tput cup 4 43; echo "$name1"
	cd $(pwd)/${name1}
	
	
	count=0
	
	for i in ${ls}
	do
	
		if [ -d $i ]; then
			tput cup $((count+5)) 45
			printf "\u2523$i"
			count=$((count+1))
		fi
		if [ $count -gt 19 ]; then
			break
		fi
		
		
	done

	
	for j in ${ls}
	do
		if [ $count -lt 20 ]; then

			if [ -f $i ]; then
				tput cup $((count+5)) 45
				printf "\u2523$j"
				count=$((count+1))
			fi
		fi
	done 
	
	tput cup $((count+5)) 45
	printf "\u2514"	

}

print_tree1() {
	array3=($(tree))
	for (( i=0; i<20; i++ ))	
	do	
		temp=array[$i]
		tput $((i+5)) 40
		printf "$temp"
	done
}	



crow=0
prow=0
nrow=$(ls -al | wc -l)
if [ $(($nrow)) -gt 20 ]; then
	nrow=20
fi

printf "[47m"
print_frame
print_pwd_info
print_dir_info
print_line 0 1
for i in {1..20}; do 
	print_line $i 0
done



while true; do
	prow=$crow

	read -r -sn1 t
	case $t in
		A) crow=$((crow-1));;
		B) crow=$((crow+1));;
		"") print_tree $prow ;;
		
	esac

	if [ $(($crow)) -lt $((0)) ]; then
		crow=0
	fi

	if [ $(($crow)) -gt $(($nrow-1)) ]; then
		crow=$(($nrow-1))
	fi
	
	print_line $prow 0
	print_line $crow 1
	
      

done

