#!/bin/bash
echo "1. 백그라운드 프로세스 두 개 실행"
(echo START1; sleep 10; echo DONE1) &
PID1=$!
(echo START2; sleep 10; echo DONE2) &
PID2=$!

echo "PID1: $PID1, PID2: $PID2"
sleep 1

echo -e "\n2. kill -STOP 첫 번째 프로세스 (프로세스 일시정지):"
kill -STOP $PID1
ps -f | grep sleep

echo -e "\n3. kill -CONT 첫 번째 프로세스 (프로세스 다시 재개):"
kill -CONT $PID1
ps -f | grep sleep

echo -e "\n4. kill -KILL 첫 번째 프로세스 (프로세스 강제종료):"
kill -KILL $PID1
ps -f | grep sleep
