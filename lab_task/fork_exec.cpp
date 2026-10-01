#include <bits/stdc++.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main() {
  pid_t pid = fork();

  if (pid < 0) {
    perror("fork");
    return 1;
  }

  // CHILD
  if (pid == 0) {
    cout << "Child PID: " << getpid() << endl;

    cout << "Parent PID: " << getppid() << endl;

    // Replace child process with clear
    execlp("clear", "clear", (char*)NULL);

    // Only executes if execlp fails
    perror("execlp");

    return 1;
  }

  // PARENT
  else {
    cout << "Parent PID: " << getpid() << endl;

    cout << "Child PID: " << pid << endl;

    wait(NULL);

    cout << "Child has finished." << endl;
  }

  return 0;
}