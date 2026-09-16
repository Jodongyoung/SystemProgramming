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