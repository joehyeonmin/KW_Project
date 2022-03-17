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
	
	elif [ `echo $name | grep -i "\.c$"` ]  && [ -f $name ]; then
		printf "[32m%-15s %-15s %-5s[30m" $name $perm $size
	
	elif [ `echo $name | grep -i "\.h$"` ] && [ -f $name ]; then
		printf "[30m%-15s %-15s %-5s[30m" $name $perm $size
	
	else
		temp=$((temp+1))
	fi

	tput cup 28 0
	
}

print_pwd_info() {
	tput cup 2 2
	printf "Current path:$(pwd)"
	tput cup 28 0
}

print_dir_info() {
	C_SIZE=0
	H_SIZE=0
	

	for file in `ls`; do 	
		if [ `echo $name | grep -i "\.c$"` ]  && [ -f $name ]; then	
			C_SIZE=$((${C_SIZE}+1))
		elif [ `echo $name | grep -i "\.h$"` ]  && [ -f $name ]; then 
			H_SIZE=$((${H_SIZE}+1))
		fi
	done



	tput cup 26 2
	printf "C file: ${C_SIZE}"
	tput cup 26 22
	printf "Header: ${H_SIZE}"
	
	tput cup 28 0
}



print_content() {
	array=($(ls -al))
        idx=$((9*$1+10))
        name=$(echo ${array1[$idx]})

	cd $(pwd)/${name1}
	
        array=($(ls -al))
        idx=$((9*$1+10))
        name=$(echo ${array1[$idx]})

	
	
	for i in {1..20}
	do
	
		if [ -f $name2 ] && [ `echo $name2 | grep -i "\.c$"` ]  ||  [ `echo $name2 | grep -i "\.h$"` ] ; then
			tput cup $(($1+4)) 45
			printf "$name%.0s"
			
		fi	
		
		
		
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

 

for i in {1..19}; do
	print_line $i 0

done




while true; do
	prow=$crow

	read -r -sn1 t
	case $t in
		A) crow=$((crow-1));;
		B) crow=$((crow+1));;
		"") print_content $prow ;;
		
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

