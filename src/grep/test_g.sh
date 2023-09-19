#!/bin/bash

echo "\033[36;1m\n\t TEST no flags \033[0m"
grep GOT ../common/1_g.txt > orig.txt
./s21_grep GOT ../common/1_g.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

grep \n ../common/2_g.txt > orig.txt
./s21_grep \n ../common/2_g.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

echo "\033[36;1m\n\t TEST -e \033[0m"
grep -e GOT ../common/1_g.txt > orig.txt
./s21_grep -e GOT ../common/1_g.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

echo "\033[36;1m\n\t TEST -o \033[0m"
grep -o GOT ../common/1_g.txt > orig.txt
./s21_grep -o GOT ../common/1_g.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

grep -o \n ../common/2_g.txt > orig.txt
./s21_grep -o \n ../common/2_g.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

echo "\033[36;1m\n\t TEST -i \033[0m"
grep -i GoT ../common/1_g.txt > orig.txt
./s21_grep -i GoT ../common/1_g.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

grep -i gOT7 ../common/1_g.txt > orig.txt
./s21_grep -i gOT7 ../common/1_g.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

echo "\033[36;1m\n\t TEST -v \033[0m"
grep -v GOT ../common/1_g.txt > orig.txt
./s21_grep -v GOT ../common/1_g.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

grep -v JJ ../common/1_g.txt > orig.txt
./s21_grep -v JJ ../common/1_g.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

echo "\033[36;1m\n\t TEST -c \033[0m"
grep -c GOT ../common/1_g.txt > orig.txt
./s21_grep -c GOT ../common/1_g.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

grep -c temp ../common/2_g.txt > orig.txt
./s21_grep -c temp ../common/2_g.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

echo "\033[36;1m\n\t TEST -n \033[0m"
grep -n GOT ../common/1_g.txt > orig.txt
./s21_grep -n GOT ../common/1_g.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

grep -n puing ../common/1c.txt > orig.txt
./s21_grep -n puing ../common/1c.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

echo "\033[36;1m\n\t TEST -h \033[0m"
grep -h GOT ../common/1_g.txt > orig.txt
./s21_grep -h GOT ../common/1_g.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

grep -h puing ../common/1c.txt > orig.txt
./s21_grep -h puing ../common/1c.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

echo "\033[36;1m\n\t TEST -l \033[0m"
grep -l GOT ../common/2_g.txt ../common/1_g.txt > orig.txt
./s21_grep -l GOT ../common/2_g.txt ../common/1_g.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt 

grep -l puing ../common/1c.txt > orig.txt
./s21_grep -l puing ../common/1c.txt > ne_orig.txt
if diff orig.txt ne_orig.txt ; then
 echo "\033[32;1m\t OK\n\033[0m"
else
 echo "\033[31;1m\t FAIL\n\033[0m"
fi
rm orig.txt ne_orig.txt
