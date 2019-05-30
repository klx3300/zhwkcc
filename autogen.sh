#!/bin/bash

SOURCEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
RECOVERDIR=$(pwd)

cd $SOURCEDIR/semantic
bison --defines=mini_c.sem.sub.hpp -o mini_c.sem.cc -r all mini_c.yxx
cd $SOURCEDIR/lexical
flex -o mini_c.lex.cc --header-file=mini_c.lex.hpp mini_c.l 

cd $RECOVERDIR
