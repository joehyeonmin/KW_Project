#!bin/bash


Print_Signin1(){
	echo "------------------------------------------------------------"
	echo "|                       MAIL BOX                           |"
        echo "------------------------------------------------------------"
	echo "                                                            "
	echo "------------------------------------------------------------"
	echo "|                                                          |"
	echo "|                                                          |"
	echo "|                     > Sign in                            |"
	echo "|                                                          |"
	echo "|                       Sign up                            |"
	echo "|                                                          |"
	echo "|                                                          |"
	echo "|                                                          |"
	echo "|                                                          |"
	echo "------------------------------------------------------------"
}

Print_Signin2(){
	echo "------------------------------------------------------------"
        echo "|                       MAIL BOX                           |"
        echo "------------------------------------------------------------"
        echo "                                                            "
        echo "------------------------------------------------------------"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                       Sign in                            |"
        echo "|                                                          |"
        echo "|                     > Sign up                            |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "------------------------------------------------------------"

}


Print_Signup1(){
        echo "------------------------------------------------------------"
        echo "|                       MAIL BOX                           |"
        echo "------------------------------------------------------------"
	echo "                                                            "
        echo "------------------------------------------------------------"
        echo "|                                                          |"
        echo "| Input ID:                                                |"
	echo "|                                                          |"
        echo "| Input password:                                          |"
	echo "|                                                          |"
        echo "| Confirme password:                                       |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                     *sign up?*                           |"
	echo "|                                                          |"
        echo "|                    yes        no                         |"
        echo "|                                                          |"
        echo "------------------------------------------------------------"
}

Print_Signup2(){
        echo "------------------------------------------------------------"
        echo "|                       MAIL BOX                           |"
        echo "------------------------------------------------------------"
        echo "                                                            "
        echo "------------------------------------------------------------"
        echo "|                                                          |"
        echo "| Input ID:                                                |"
        echo "|                                                          |"
        echo "| Input password:                                          |"
        echo "|                                                          |"
        echo "| Confirme password:                                       |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                     *sign up?*                           |"
        echo "|                                                          |"
        echo "|                >   yes        no                         |"
        echo "|                                                          |"
        echo "------------------------------------------------------------"
}

Print_Signup3(){
        echo "------------------------------------------------------------"
        echo "|                       MAIL BOX                           |"
        echo "------------------------------------------------------------"
        echo "                                                            "
        echo "------------------------------------------------------------"
        echo "|                                                          |"
        echo "| Input ID:                                                |"
        echo "|                                                          |"
        echo "| Input password:                                          |"
        echo "|                                                          |"
        echo "| Confirme password:                                       |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                     *sign up?*                           |"
        echo "|                                                          |"
        echo "|                    yes     >  no                         |"
        echo "|                                                          |"
        echo "------------------------------------------------------------"
}

Signin(){
	crow=1
	temp=1
	while true; do

        read -r -sn1 t
        case $t in
        A) clear
           crow=0
           Print_Signin1
           ;;
        B) clear
           crow=1
           Print_Signin2
           ;;
        "") clear
             if [ $crow = 0 ]; then
                clear
                Print_Signin
                Con_Signin $name $password1 $password2
             fi
             if [ $crow = 1 ]; then
                clear
                Print_Signup1
                Signup 
             fi
             ;;


             esac
	done

}

Signup(){
	tput cup 6 12
	read name
	tput cup 8 18
	read -s password1
	tput cup 10 21
	read -s password2

	if [ $password1 == $password2 ]; then
		clear
		Print_Signup2
		tput cup 6 12
		echo "$name"
		prow=1
		while true; do
		        read -r -sn1 t
    		        case $t in
               		 C) clear
                   		prow=0
				Print_Signup3
				tput cup 6 12
				echo "$name"
                		;;
                	 D) clear
                   		prow=1
				Print_Signup2
				tput cup 6 12
				echo "$name"
				;;
               		 "") clear
		        	if [ $prow == 1 ]; then
                        		clear
					Print_Signin
					Con_Signin $name $password1
				fi                    		
                    		
				if [ $prow == 0 ]; then
                        		clear
					Print_Signup1
					Signup 
                       			
                   		fi
                    		;;
			esac
			
               done
	

	else
		clear; Print_Signup1; Signup

	fi
}




Print_Signin(){
	echo "------------------------------------------------------------"
        echo "|                       MAIL BOX                           |"
        echo "------------------------------------------------------------"
        echo "                                                            "
        echo "------------------------------------------------------------"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|  ID:                                                     |"
        echo "|                                                          |"
        echo "|  password:                                               |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "------------------------------------------------------------"
}

Con_Signin(){
	tput cup 7 7
	read username
	tput cup 9 14
	read -s userpassword	
	

	if [ $username == $1 ]&& [ $userpassword == $2 ]; then
		clear
		Print_Signmain
		tput cup 3 7
		echo "$1"
		Signmain
	else
		clear
		Print_Signin
		Con_Signin $1 $2
	fi


}

Print_Signmain(){
        echo "------------------------------------------------------------"
        echo "|                        MAIL BOX                          |"
        echo "------------------------------------------------------------"
        echo "|user:                                                     |"
        echo "------------------------------------------------------------"
        echo "|                                                          |"
        echo "|                        read mail                         |"
        echo "|                                                          |"
        echo "|                        send mail                         |"
        echo "|                                                          |"
        echo "|                        sended                            |"
        echo "|                                                          |"
        echo "|                        search                            |"
        echo "|                                                          |"
	echo "|                        trash can                         |"
        echo "|                                                          |"
 	echo "|                        exit                              |"
        echo "------------------------------------------------------------"
}



Print_sele(){
	

	tput cup $(($1*2+6)) 18
	echo ">"
}

Delete_sele(){

        tput cup $((($1*2)+6)) 18
        echo " "
}


Signmain(){
	crow=0
        temp=1
        while true; do
		
        read -r -sn1 t
        case $t in
        A)  Delete_sele $crow

		crow=$((crow-1))
           
           ;;
        B)  Delete_sele $crow

		crow=$((crow+1))
          

           ;;
        "") clear
                if [ $crow = 0 ]; then
                clear
                Print_readmail1
                fi

                if [ $crow = 1 ]; then
                clear
                Print_sendmail1
                fi

	        if [ $crow = 2 ]; then
                clear
                Print_sended
                fi

		if [ $crow = 3 ]; then
                clear
                Print_search
                fi

		if [ $crow = 4 ]; then
                clear
                Print_trashcan
                fi

		if [ $crow = 5 ]; then
                clear
                Print_exit
	        fi

	esac
	
	if [ $crow -lt 0 ]; then
		crow=0
	fi
	if [ $crow -gt 6 ]; then
		crow=6
	fi

	Print_sele $crow

done
}
Print_readmail1(){
        echo "------------------------------------------------------------"
        echo "|                   MAIL BOX                               |"
        echo "------------------------------------------------------------"
        echo "|user:                                                     |"
        echo "------------------------------------------------------------"
        echo "|      prev                                                |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "------------------------------------------------------------"
}

Print_readmail2(){
        echo "------------------------------------------------------------"
        echo "from.                                                       "
        echo "------------------------------------------------------------"
        echo "title:                                                     |"
        echo "------------------------------------------------------------"
        echo "content:                                                    "
}

Print_sendmail1(){
        echo "------------------------------------------------------------"
        echo "|                   MAIL BOX                               |"
        echo "------------------------------------------------------------"
        echo "|user:                                                     |"
        echo "------------------------------------------------------------"
        echo "| who?                                                     |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "------------------------------------------------------------"
}

Print_sendmail2(){
        echo "------------------------------------------------------------"
        echo "to.                                                       "
        echo "------------------------------------------------------------"
        echo "title:                                                     |"
        echo "------------------------------------------------------------"
        echo "content:                                                    "
}

Print_sendmail3(){
	bash project1.sh


}

Print_sended(){
        echo "------------------------------------------------------------"
        echo "|                   MAIL BOX                               |"
        echo "------------------------------------------------------------"
        echo "|user:                                                     |"
        echo "------------------------------------------------------------"
        echo "| > prev                                                   |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "------------------------------------------------------------"
}


Print_search(){
        echo "------------------------------------------------------------"
        echo "|                   MAIL BOX                               |"
        echo "------------------------------------------------------------"
        echo "|user:                                                     |"
        echo "------------------------------------------------------------"
        echo "| search:                                                     |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "------------------------------------------------------------"
}

Print_trashcan(){
        echo "------------------------------------------------------------"
        echo "|                   MAIL BOX                               |"
        echo "------------------------------------------------------------"
        echo "|user:                                                     |"
        echo "------------------------------------------------------------"
        echo "| who?                                                     |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "------------------------------------------------------------"
}

Print_exit(){
        echo "------------------------------------------------------------"
        echo "|                   MAIL BOX                               |"
        echo "------------------------------------------------------------"
        echo "|                                                          |"
        echo "------------------------------------------------------------"
        echo "| exit program                                             |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "|                                                          |"
        echo "------------------------------------------------------------"
}


Print_Signin1
Signin

