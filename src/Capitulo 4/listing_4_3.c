int main() {
  pthread_t thread1_id;
  pthread_t thread2_id;
  struct char_print_parms thread1_args;
  struct char_print_parms thread2_args;
  /* Create a new thread to print 30,000 x's. */
  thread1_args.character = 'x';
  thread1_args.count = 30000;
  pthread_create(&thread1_id, NULL, &char_print, &thread1_args);
  /* Create a new thread to print 20,000 o's. */
  thread2_args.character = 'o';
  thread2_args.count = 20000;
  pthread_create(&thread2_id, NULL, &char_print, &thread2_args);
  /* Make sure the first thread has finished. */
  pthread_join(thread1_id, NULL);
  /* Make sure the second thread has finished. */
  pthread_join(thread2_id, NULL);
  /* Now we can safely return. */
  return 0;
}