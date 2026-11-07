#!/bin/bash

buildApplication() {
    # If TARGET is not defined, default to the export stage
    if [ -z "$TARGET" ]; then
        TARGET=export
    fi
    docker build --target $TARGET \
                 --output type=local,dest=build \
                 . $@
}

buildDoc() {
    # Ensure the documentation output folder exists
    # before running the container
    # (helps avoid file permission errors)
    if [ ! -d "build/doc" ]; then
        mkdir --parents build/doc
    fi
    docker run --user $(id -u):$(id -g) \
               --volume "$(pwd)":/data \
               --rm hrektts/doxygen \
               doxygen Doxyfile
}

build() {
    case "$PROJECT" in
        "all")
            buildApplication
            ;&
        "doc")
            buildDoc
            ;;
        "sudoSolve")
            buildApplication
            ;;
        *)
            printf "Provided project \"%s\" not a valid option" "$PROJECT"
            exit 1
    esac
}

printHelp() {
    printf "Usage: %s [options]\n" $0
    printf "Options:\n"
    printf "  -p [ --project ] <PROJECT>
            \t\tProject to build. One of: [doc, sudoSolve].
            \t\tDefaults to building all if not provided.\n"
    printf "  -t [ --target ] <TARGET>
            \t\tTarget of project to build. Only available for project "sudoSolve".
            \t\tPassed to --target option of docker build.\n"
    exit 0
}

for ARG in $@
do
    if [ "$ARG" = "-h" ] || [ "$ARG" = "--help" ]; then
        printHelp
        exit 0
    elif [ "$ARG" = "-p" ] || [ "$ARG" = "--project" ]; then
        PROJECT="$2"
        shift 2
    elif [ "$ARG" = "-t" ] || [ "$ARG" = "--target" ]; then
        TARGET="$2"
        shift 2
    fi
done

if [ -z "$PROJECT" ]; then
    PROJECT=all
fi

build $@