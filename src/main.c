/*
 *   Purpose: A learning project to write my own John The Ripper in Rust!
 *
 * Pass a hash value and a word list to crack hashed passwords!
 * Can also be
 * used to quickly generate hashes of a wordlist (not
 * implemented yet)
 *
 *
 * Author: Mauzy0x00
 *   Date:   12.11.2024
 *
 *   Forker: Sinnaminty
 * Date
 * 2.17.2025
 *   NOTE: c is cute. rust is for smart people. I am neither.
 *
 */

#include <openssl/evp.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  char *hash_type;
  char *target_hash;
  char *wordlist;
  int threads;
} Args;

void parse_args(int argc, char *argv[], Args *args) {
  int opt;
  while ((opt = getopt(argc, argv, "t:h:w:p:")) != -1) {
    switch (opt) {
    case 't':
      args->hash_type = optarg;
      break;

    case 'h':
      args->target_hash = optarg;
      break;

    case 'w':
      args->wordlist = optarg;
      break;

    case 'p':
      args->threads = atoi(optarg);
      break;

    default:
      fprintf(stderr,
              "Usage: %s -t <hash_type> -h <hash> -w <wordlist> -p <threads>\n",
              argv[0]);
      exit(EXIT_FAILURE);
    }
  }
}

void print_help() {
  printf("Usage: -t <hash_type> -h <hash> -w <wordlist> -p <threads>\n");
  return;
}

void *crack_hash(void *arg) {

  printf("Thread started\n");
  return NULL;
}

int main(int argc, char *argv[]) {
  Args args = {NULL, NULL, NULL, 1};
  parse_args(argc, argv, &args);

  if (!args.hash_type || !args.target_hash || !args.wordlist) {
    fprintf(stderr, "Missing required arguments\n");
    print_help();
    exit(EXIT_FAILURE);
  }

  FILE *file = fopen(args.wordlist, "r");
  if (!file) {
    perror("Error opening wordlist");
    exit(EXIT_FAILURE);
  }

  pthread_t threads[args.threads];
  for (int i = 0; i < args.threads; i++) {
    pthread_create(&threads[i], NULL, crack_hash, NULL);
  }

  for (int i = 0; i < args.threads; i++) {
    pthread_join(threads[i], NULL);
  }

  fclose(file);
  return 0;
}
