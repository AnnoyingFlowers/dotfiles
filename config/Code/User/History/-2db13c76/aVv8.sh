#!/bin/bash
set -e

echo "Create database db.dat"
./build/ex17_sub.out db.dat c 100 512

echo "Set 1 foo 111222 foo@bar.com"
./build/ex17_sub.out db.dat s 1 foo 111222 foo@bar.com

echo "Set 2 baz 333444 baz@qux.com"
./build/ex17_sub.out db.dat s 2 baz 333444 baz@qux.com

echo "Printing all records"
./build/ex17_sub.out db.dat l

echo "Find which phone is 111222"
./build/ex17_sub.out db.dat f 111222

echo "Deleting record 1"
./build/ex17_sub.out db.dat d 1

echo "Getting record 2"
./build/ex17_sub.out db.dat g 2