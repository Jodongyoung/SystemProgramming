#!/bin/bash
echo "1. 백그라운드로 sleep 100 두 번 실행"
sleep 100 &
sleep 100 &

echo -e "\n2. jobs 명령어 실행:"
jobs

echo -e "\n3. ps -f 실행 (현재 프로세스 목록 확인):"
ps -f

echo -e "\n4. kill %1 실행 (1번 작업 종료):"
kill %1

echo -e "\n5. 종료 후 ps -f 다시 확인:"
ps -f

# 남아있는 2번 백그라운드 작업 정리
kill %2 2>/dev/null
