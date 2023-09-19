#!/bin/bash

echo "\033[36;1m\n\t TEST no flags \033[0m"
cat ../common/1c.txt > orig.txt
./s21_cat ../common/1c.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

cat ../common/1c.txt ../common/1_g.txt > orig.txt
./s21_cat ../common/1c.txt ../common/1_g.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

echo "\033[36;1m\n\t TEST -b \033[0m"
cat -b ../common/1c.txt > orig.txt
./s21_cat -b ../common/1c.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

cat -b ../common/1c.txt ../common/1_g.txt > orig.txt
./s21_cat -b ../common/1c.txt ../common/1_g.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

echo "\033[36;1m\n\t TEST -e \033[0m"
cat -e ../common/1c.txt > orig.txt
./s21_cat -e ../common/1c.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

cat -e ../common/1c.txt ../common/1_g.txt > orig.txt
./s21_cat -e ../common/1c.txt ../common/1_g.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

echo "\033[36;1m\n\t TEST -n \033[0m"
cat -n ../common/1c.txt > orig.txt
./s21_cat -n ../common/1c.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

cat -n ../common/1c.txt ../common/1_g.txt > orig.txt
./s21_cat -n ../common/1c.txt ../common/1_g.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

echo "\033[36;1m\n\t TEST -s \033[0m"
cat -s ../common/1c.txt > orig.txt
./s21_cat -s ../common/1c.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

cat -s ../common/1c.txt ../common/1_g.txt > orig.txt
./s21_cat -s ../common/1c.txt ../common/1_g.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

echo "\033[36;1m\n\t TEST -t \033[0m"
cat -t ../common/1c.txt > orig.txt
./s21_cat -t ../common/1c.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

cat -t ../common/1c.txt ../common/1_g.txt > orig.txt
./s21_cat -t ../common/1c.txt ../common/1_g.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 
