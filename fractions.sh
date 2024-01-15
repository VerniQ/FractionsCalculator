#!/bin/bash

#Skrypt Bash do programu napisanego w języku C, sposób działania większośći rzeczy jest taki sam jak w drugim programie. Pozostałe rzeczy zostaną wyjaśnione

gcd() { #Największy wspólny dzielnik
    if [ "$#" -ne 2 ]; then
        echo "Invalid input"
        return 1
    fi

    a=$1
    b=$2

    if [[ ! $a =~ ^[0-9]+$ || ! $b =~ ^[0-9]+$ ]]; then
        echo "Invalid input"
        return 1
    fi

    while [ $b -ne 0 ]; do
        remainder=$((a % b))
        a=$b
        b=$remainder
    done

    echo "$a"
}

abs() { #Język Bash nie posiada wbudowanej funkcji odpowiadającej za zwracanie wartości bezwzględnej, dlatego została stworzona.
    if [ $1 -lt 0 ]; then
        echo $((-$1))
    else
        echo $1
    fi
}
printFraction() { #Funkcja wypisująca ułamki w postaci właściwej, schemat działania identyczny jak w przypadku drugiego programu.
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
    if [ $a -eq $b ]; then
        echo "1"
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

#Funkcje wykonujące działania na ułamkach, sposób działania identyczny jak w programie w języku C

sum() {
    a=$1
    b=$2
    c=$3
    d=$4

    numerator=$(((a * d) + (c * b)))
    denominator=$((b * d))

    printFraction $numerator $denominator
}

sub() {
    a=$1
    b=$2
    c=$3
    d=$4

    numerator=$((a * d - c * b))
    denominator=$((b * d))

    printFraction $numerator $denominator
}

mul() {
    a=$1
    b=$2
    c=$3
    d=$4

    numerator=$((a * c))
    denominator=$((b * d))

    printFraction $numerator $denominator
}

quo() {
    a=$1
    b=$2
    c=$3
    d=$4

    numerator=$((a * d))
    denominator=$((b * c))

    printFraction $numerator $denominator
}

#Wykonywanie odpowiedniego działania na podstawie znaku wprowadzonego przez użytkowanika, sposób działania identyczny jak w programie w języku C

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

    case "$operation" in
        +)
            sum "$1" "$2" "$3" "$4"
            ;;
        -)
            sub "$1" "$2" "$3" "$4"
            ;;
        /)
            quo "$1" "$2" "$3" "$4"
            ;;
        *)
            mul "$1" "$2" "$3" "$4"
            ;;
    esac
}

#Funkcje wczytujące ułamek oraz znak działania, sposób działania identyczny jak w języku C, program prosi o podanie wartości do momentu wprowadzenia ułamków w odpowienij formie oraz odpowiedniego znaku

readFraction() {
    while true; do
        read -p "Podaj ulamek w formacie a/b: " input

        if [[ "$input" =~ ^[0-9]+/[0-9]+$ ]]; then
            IFS='/' read -r numerator denominator <<< "$input"
            echo "$numerator $denominator"
            break
        else
            echo "Błędny format. Podaj ulamek w formacie a/b."
            echo "NaN NaN"
            break
        fi
    done
}
readFraction() {
    while true; do
        read -p "Podaj ulamek w formacie a/b: " input

        if [[ "$input" =~ ^-?[0-9]+/-?[0-9]+$ ]]; then
            IFS='/' read -r numerator denominator <<< "$input"
            echo "$numerator $denominator"
            break
        else
            echo "Błędny format. Podaj ulamek w formacie a/b."
        fi
    done
}
readOperation() {
    local operation
    while true; do
        read -p "Wprowadz dzialanie (+, -, *, /): " operation
        case $operation in
            [+-/*]) break ;;
            *) echo "Bledne dzialanie. Wprowadz ponownie." ;;
        esac
    done
    echo "$operation"
}

#Poniższy kod odpowiada funkcji main() w języku C, wywoływane są tu funkcje.

echo "Wprowadź pierwszy ułamek:"
read -r numerator1 denominator1 <<< "$(readFraction)"

echo "Wprowadź drugi ułamek:"
read -r numerator2 denominator2 <<< "$(readFraction)"

operation=$(readOperation)
if [ "$operation" = '/' ] && [ "$numerator1" -eq 0 ]; then
    echo "Błąd! Dzielenie przez zero jest niewykonywalne!"
    exit
else
    fractionOperation $numerator1 $denominator1 $numerator2 $denominator2 "$operation"
fi
