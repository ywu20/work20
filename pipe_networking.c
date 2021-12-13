#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  int from_client = 0;
  mkfifo("well_known", 0644);
  int well_known = open("well_known",O_RDONLY);
  printf("Open well known pipe\n");
  char secret_name[10];
  read(well_known, secret_name,10);
  int secret = open(secret_name,O_WRONLY,10);
  printf("Open well secret pipe\n");
  printf("secret_name:%s\n",secret_name);
  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server = 0;
  char secret_name [10] = "secret";//strcat("secret", getpid());//itoa(getpid());
  mkfifo(secret_name, 0644);
  int well_known = open("well_known", O_WRONLY);
  printf("Open well known pipe\n");
  write(well_known, secret_name, sizeof(secret_name));
  int secret = open(secret_name, O_RDONLY);
  printf("Open well secret pipe\n");

  return from_server;
}
