#!/bin/bash

gcc main.c ibqs.c qsin.c fitas.c intercalacao.c qSortExt.c -o main
./main $1 $2 $3 $4
