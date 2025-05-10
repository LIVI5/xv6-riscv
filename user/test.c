#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void workload(int runtime) {
  // 지정된 runtime 동안 busy-wait
  volatile int i;
  for (int t = 0; t < runtime; t++) {
    ps(0); // 프로세스 상태 출력?
    for (i = 0; i < 1000000; i++) {
      // Busy-wait loop
    }
    // 현재 실행 중인 프로세스 출력
    printf("Currently running process: %d\n", getpid());
  }
}

int main() {
  int pid;
  int num_processes = 3; // 테스트할 프로세스 수를 3개로 줄임
  int priorities[] = {5, 20, 35}; // 각 프로세스의 nice 값
  int runtime = 10; // 각 프로세스가 실행할 workload 시간을 늘림

  printf("EEVDF test start\n");

  // 여러 프로세스 생성
  for (int i = 0; i < num_processes; i++) {
    pid = fork();
    if (pid == 0) {
      // 자식 프로세스: nice 값 설정 후 workload 실행
      setnice(getpid(), priorities[i]);
      printf("process %d: nice=%d start\n", getpid(), priorities[i]);
      workload(runtime);
      printf("process %d: done\n", getpid());
      exit(0);
    }
  }

  // 부모 프로세스: 모든 자식 프로세스가 종료될 때까지 대기
  for (int i = 0; i < num_processes; i++) {
    wait(0);
  }

  // 스케줄링 결과 출력
  printf("EEVDF done\n");

  exit(0);
}