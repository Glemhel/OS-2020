# !/bin/bash
# initially file "ex2a_file" consists only of "1\n" - see "ex2a_run.sh"
x=0
while [[ $x -le 100 ]] # in file, there will be numbers 1..100 inclusively
do
    if ln ex2a_file ex2a_file.lock # if successfully created, i.e. file is not busy now
	then
        # by entering this condition, we locked the file
        x=$( tail -n1 ex2a_file.lock )
        x=$(( $x + 1 ))
        if [[ $x -le 100 ]] # we only append numbers that are <= 100
        then
            echo "$x" >> ex2a_file.lock
        fi
        rm ex2a_file.lock # unlocking the file for other processes
    fi
done
# Results that I got is presented in "ex2a_file" - numbers are not shuffled. 
# Race prevented successfully (30 trials - everything is fine).
# Critical region is locked by "ln" function.