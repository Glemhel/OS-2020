# !/bin/bash
# initially file "ex2_file" consists only of "1\n" - see "ex2_run.sh"
x=1
while [[ $x -lt 10 ]] # in file, there will be numbers 1..10 inclusively
do
    x=$( tail -n1 ex2_file )
    x=$(($x + 1))
    echo "$x" >> ex2_file
done
# Results that I got is presented in "ex2_file" - we see that some numbers are duplicated. I got shuffled results on the first
# execution.
# Critical region is "ex2_file" itself, as both processes may have read the same last line and then appended number + 1 
# twice after it.
# Modification is in file "ex2a.sh"