cmake_minimum_required(VERSION 3.20)
project(make_new_project C)

set(CMAKE_C_STANDARD 99)

# ---------------------------------------------
# 연습문제 (Practice)
# ---------------------------------------------
# 3-1: 5문장 길이순 정렬
add_executable(practice_3_1
        ch03/practice/3-1/main.c
        ch03/practice/3-1/copy.c
        ch03/practice/3-1/copy.h
)

# 3-2: 디버깅 검사용
add_executable(practice_3_2
        ch03/practice/3-2/main.c
        ch03/practice/3-2/copy.c
        ch03/practice/3-2/copy.h
)

# 3-3: 파일 입출력 5개 모듈
add_executable(practice_3_3
        ch03/practice/3-3/main.c
        ch03/practice/3-3/Write.c
        ch03/practice/3-3/Write.h
        ch03/practice/3-3/Read.c
        ch03/practice/3-3/Read.h
)

# ---------------------------------------------
# 정규 과제 (Homework)
# ---------------------------------------------
# task01: 과제 1~3번 다중 모듈
add_executable(hw_task01
        ch03/homework/task01/main.c
        ch03/homework/task01/copy.c
        ch03/homework/task01/copy.h
)
# --- Chapter 04 Practice ---
add_executable(practice_4_1 ch04/practice/ex01/main.c)
add_executable(practice_4_2 ch04/practice/ex02/main.c)
add_executable(practice_4_3 ch04/practice/ex03/main.c)
add_executable(practice_4_4 ch04/practice/ex04/main.c)
add_executable(practice_4_5 ch04/practice/ex05/main.c)
add_executable(practice_4_6 ch04/practice/ex06/main.c)
add_executable(practice_4_7 ch04/practice/ex07/main.c)
add_executable(practice_4_8 ch04/practice/ex08/main.c)

# --- Chapter 04 Homework ---
add_executable(hw_4_task01 ch04/homework/task01/append.c)
add_executable(hw_4_task02 ch04/homework/task02/cat.c)
add_executable(practice_5_1 ch05/practice/ex01/fopen.c)
add_executable(practice_5_3 ch05/practice/ex03/copy.c)
add_executable(practice_5_2 ch05/practice/ex02/fsize.c)
add_executable(practice_5_4 ch05/practice/ex04/dup.c)
add_executable(practice_5_5 ch05/practice/ex05/dbcreate.c)
add_executable(practice_5_6 ch05/practice/ex06/dbquery.c)
add_executable(practice_5_7 ch05/practice/ex07/dbupdate.c)
add_executable(homework_5_1 ch05/homework/task01/task01.c)
add_executable(homework_5_2 ch05/homework/task02/task02.c)

# ==========================================
# Chapter 06: 파일 시스템 실습 및 과제
# ==========================================
add_executable(practice_6_1 ch06/practice/ex01/ftype.c)
add_executable(practice_6_2 ch06/practice/ex02/fchmod.c)
add_executable(practice_6_3 ch06/practice/ex03/cptime.c)
add_executable(practice_6_4 ch06/practice/ex04/list_1.c)
add_executable(practice_6_5 ch06/practice/ex05/list_2.c)
add_executable(practice_6_6 ch06/practice/ex06/link.c)
add_executable(practice_6_7 ch06/practice/ex07/unlink.c)
add_executable(practice_6_8 ch06/practice/ex08/slink.c)
add_executable(practice_6_9 ch06/practice/ex09/rlink.c)
add_executable(homework_6_1 ch06/homework/task01/task01.c)
add_executable(homework_6_2 ch06/homework/task02/list_opt.c)
# ================= 10장 실습 및 과제 =================
add_executable(ch10_train1 ch10/train_1/stud1.c)
add_executable(ch10_train2 ch10/train_2/stud2.c)
add_executable(ch10_train3 ch10/train_3/mem.c)
add_executable(ch10_task01 ch10/homework/task01/main.c)
add_executable(ch10_task02 ch10/homework/task02/main.c)

# ================= 11장 및 12장 과제 =================
add_executable(ch11_task01 ch11/homework/task01/main.c)
add_executable(ch12_task01 ch12/homework/task01/main.c)
add_executable(ch12_task02 ch12/homework/task02/main.c)
add_executable(ch12_task03 ch12/homework/task03/main.c)
