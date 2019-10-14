if [ -z $1 ]
then
    echo
    echo "Usage: $0 <source file>"
    echo
    exit 1
fi

SRC_FILE=$1
BIN_NAME=$(echo $SRC_FILE | cut -d'.' -f 1)
clang++ -std=c++17 -Wall $SRC_FILE -o $BIN_NAME