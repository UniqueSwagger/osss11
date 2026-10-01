#include <bits/stdc++.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main() {
  int fd[2];

  // Create pipe
  if (pipe(fd) == -1) {
    perror("pipe");
    return 1;
  }

  pid_t pid = fork();

  if (pid < 0) {
    perror("fork");
    return 1;
  }

  // PARENT
  if (pid > 0) {
    // Parent does not read
    close(fd[0]);

    string message = "Hello from the Parent via Pipe!";

    write(fd[1], message.c_str(), message.size() + 1);

    close(fd[1]);

    wait(NULL);
  }

  // CHILD
  else {
    // Child does not write
    close(fd[1]);

    char buffer[100];

    read(fd[0], buffer, sizeof(buffer));

    cout << "Child received: " << buffer << endl;

    close(fd[0]);

    // Replace child with whoami
    execlp("whoami", "whoami", (char*)NULL);

    // Runs only if execlp fails
    perror("execlp");
    return 1;
  }

  return 0;
}