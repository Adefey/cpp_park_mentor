 #!/usr/bin/env bash

set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

function check_log() {
    LOG=$( { ${1}; } 2>&1 )
    STATUS=$?
    echo "$LOG"
    if echo "$LOG" | grep -q -E "${2}"
    then
        exit 1
    fi

    if [ $STATUS -ne 0 ]
    then
        exit $STATUS
    fi
}


print_header "RUN clang-tidy"
check_log "clang-tidy ./include/*.hpp ./src/*.cpp ./test/*.cpp -extra-arg=-std=c++2a -- -I./include" "Error (?:reading|while processing)"

print_header "SUCCESS"
