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


print_header "RUN cppcheck"
check_log "cppcheck --enable=all --inconclusive --error-exitcode=1 ../include/* ../src/* ../test/* --suppress=missingIncludeSystem --suppress=unmatchedSuppression --suppress=useStlAlgorithm" "\(information\)"

print_header "RUN clang-tidy"
check_log "clang-tidy ../include/* ../src/* ../test/* -warnings-as-errors=* -extra-arg=-std=c++2a -- -I./include -I ../libs/network/include/ -I ../libs/data_processing/include/" "Error (?:reading|while processing)"

print_header "RUN cpplint"
check_log "cpplint --extensions=cpp,hpp --filter=-build/header_guard,-legal/copyright,-runtime/explicit,-whitespace/blank_line,-whitespace/comments,-whitespace/indent,-runtime/string,-runtime/references ../include/* ../src/* ../test/*" "Can't open for reading"

print_header "SUCCESS"
