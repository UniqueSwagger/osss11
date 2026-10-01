#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

struct SharedMemory {
  int flag;
  char message[1024];
};

int main() {
  const char* name = "/my_shared_memory";

  // Create shared memory
  int fd = shm_open(name, O_CREAT | O_RDWR, 0666);

  if (fd == -1) {
    perror("shm_open");
    return 1;
  }

  // Give shared memory enough size
  ftruncate(fd, sizeof(SharedMemory));

  // Map shared memory
  SharedMemory* shared = (SharedMemory*)mmap(
      NULL, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  if (shared == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  shared->flag = 0;

  pid_t pid = fork();

  if (pid < 0) {
    perror("fork");
    return 1;
  }

  // CHILD
  if (pid == 0) {
    // Wait until parent writes
    while (shared->flag != 1);

    cout << "Child received: " << shared->message << endl;

    strcpy(shared->message, "Hello from Child!");

    shared->flag = 2;

    munmap(shared, sizeof(SharedMemory));
    close(fd);

    return 0;
  }

  // PARENT
  else {
    cout << "Enter message: ";
    cin.getline(shared->message, 1024);

    // Tell child message is ready
    shared->flag = 1;

    wait(NULL);

    if (shared->flag == 2) {
      cout << "Parent received: " << shared->message << endl;
    }

    munmap(shared, sizeof(SharedMemory));
    close(fd);
    shm_unlink(name);
  }

  return 0;
}