#!/bin/bash

gcd() {
    # Ensure two arguments are provided
    if [ "$#" -ne 2 ]; then
        echo "Invalid input"
        return 1
    fi

    a=$1
    b=$2

    # Ensure both inputs are non-negative integers
    if [[ ! $a =~ ^[0-9]+$ || ! $b =~ ^[0-9]+$ ]]; then
        echo "Invalid input"
        return 1
    fi

    # Euclidean algorithm for finding GCD
    while [ $b -ne 0 ]; do
        remainder=$((a % b))
        a=$b
        b=$remainder
    done

    echo "$a"
}

abs() {
    if [ $1 -lt 0 ]; then
        echo $((-$1))
    else
        echo $1
    fi
}
sum() {
    a=$1
    b=$2

    c=$3
    d=$4

    numerator=$((a * d + c * b))
    denominator=$((b * d))
    printFraction $numerator $denominator
}
sub(){
    a=$1
    b=$2

    c=$3
    d=$4
    numerator=$((a*d-c*d))
    denominator=$((b*d))
    printFraction $numerator $denominator
}
mul(){
    a=$1
    b=$2

    c=$3
    d=$4
    numerator=$((a*c))
    denominator=$((b*d))
    printFraction $numerator $denominator
}
quo(){
    a=$1
    b=$2

    c=$3
    d=$4
    numerator=$((a*d))
    denominator=$((b*c))
    printFraction $numerator $denominator

}
fractionOperation() {
    a=$1
    b=$2
    c=$3
    d=$4
    operation=$5
    printFraction $a $b
    echo "$operation"
    printFraction $c $d
    echo "="

    if [ $operation -eq 1 ]; then
        sum $a $b $c $d
    elif [ $operation -eq 2 ]; then
        sub $a $b $c $d
    elif [ $operation -eq 3 ]; then
        mul $a $b $c $d
    elif [ $operation -eq 4 ]; then
        quo $a $b $c $d
    fi
}
fractionOperationCase() {
    a=$1
    b=$2
    c=$3
    d=$4
    operation=$5

    case "$operation" in
        +) 
            sum "$a" "$b" "$c" "$d"
            ;;
        -)
            sub "$a" "$b" "$c" "$d"
            ;;  
        %)
            quo "$a" "$b" "$c" "$d"
            ;;  
        *)
            mul "$a" "$b" "$c" "$d"
            ;;
    esac
}
printFraction() {
    a=$1
    b=$2
    abs_a=$(abs $a)
    abs_b=$(abs $b)

    if [ $b -eq 0 ]; then
        echo "NaN"
        return 
    fi

    if [ $a -eq 0 ]; then
        echo "0"
        return 
    fi

    gcd_temp=$(gcd $abs_a $abs_b)
    if [ $((abs_a)) -lt $((abs_b)) ]; then

        if [ "$gcd_temp" -ne 1 ]; then
            if [ $a -lt 0 ] || [ $b -lt 0 ]; then
                if [ $a -lt 0 ] && [ $b -lt 0 ]; then
                    temp_numerator=$(($abs_a / gcd_temp))
                    temp_denominator=$(($abs_b / gcd_temp))
                    echo "$temp_numerator/$temp_denominator"
                    return
                else
                    temp_numerator=$(( $abs_a / gcd_temp ))
                    temp_denominator=$(( $abs_b / gcd_temp ))
                    echo "-$temp_numerator/$temp_denominator"
                    return
                fi
            else
                temp_numerator=$((a / gcd_temp))
                temp_denominator=$((b / gcd_temp))
                echo "$temp_numerator/$temp_denominator"
                return
            fi
        else
            if [ $a -lt 0 ] || [ $b -lt 0 ]; then
                if [ $a -lt 0 ] && [ $b -lt 0 ]; then
                    echo "$abs_a/$abs_b"
                    return
                else
                    temp_numerator=$abs_a
                    temp_denominator=$abs_b
                    echo "-$temp_numerator/$temp_denominator"
                    return
                fi
            else
                echo "$a/$b"
                return
            fi
        fi
    else
        gcd_temp=$(gcd $abs_a $abs_b)
        if [ "$gcd_temp" -ne 1 ]; then
            modulo=$((abs_a%abs_b))
            if [ $modulo -eq 0 ]; then
                if [ $a -lt 0 ] || [ $b -lt 0 ]; then 
                    if [ $a -lt 0 ] && [ $b -lt 0 ]; then
                        temp=$(($abs_a/$abs_b))
                        echo "$temp"
                        return
                    else
                        temp=$(($abs_a/$abs_b))
                        echo "-$temp"
                        return
                    fi

                else
                    temp=$(($abs_a/$abs_b))
                    echo "$temp"
                    return
                fi
            else
                reduceNominator=$((abs_a / gcd_temp))
                reduceDenominator=$((abs_b / gcd_temp))
                temp=$((reduceNominator/reduceDenominator))        
                temp2=$((reduceNominator%reduceDenominator))
                if [ $a -lt 0 ] || [ $b -lt 0 ]; then
                    if [ $a -lt 0 ] && [ $b -lt 0 ]; then
                        echo "$temp $temp2/$abs_b"
                        return
                    else
                        echo "-$temp $temp2/$abs_b"
                        return
                    fi
                else
                    echo "$temp $temp2/$abs_b"
                    return
                fi
            fi
        else 
            temp=$((abs_a/abs_b))
            temp2=$((abs_a%abs_b))
            if [ $a -lt 0 ] || [ $b -lt 0 ]; then 
                if [ $a -lt 0 ] && [ $b -lt 0 ]; then
                    echo "$temp $temp2/$abs_b"
                    return
                else
                    echo "-$temp $temp2/$abs_b"
                    return
                fi
            else
                echo "$temp $temp2/$abs_b"
                return
            fi
        fi
    fi
}
IFS='/' read -p "Podaj ulamek w formacie a/b: " numerator1 denominator1
echo "Numerator: $numerator1"
echo "Denominator: $denominator1"

IFS='/' read -p "Podaj ulamek w formacie a/b: " numerator2 denominator2
echo "Numerator: $numerator2"
echo "Denominator: $denominator2"

read -p "Podaj działanie do wykonania( +, -, *, %)" operation
echo "Operation: $operation"

fractionOperationCase $numerator1 $denominator1 $numerator2 $denominator2 $operation



