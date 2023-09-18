#include <pthread.h>
#include <stdio.h>
#include <string.h>

/* An array of balances in accounts, indexed by account number. */
float account_balances[] = {1000.0, 2000.0, 54020.4};
/* Transfer DOLLARS from account FROM_ACCT to account TO_ACCT. Return
 0 if the transaction succeeded, or 1 if the balance FROM_ACCT is
 too small. */

int process_transaction(int from_acct, int to_acct, float dollars) {
  int old_cancel_state;

  /* Check the balance in FROM_ACCT. */
  if (account_balances[from_acct] < dollars)
    return 1;

  /* Begin critical section. */
  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
  /* Move the money. */
  account_balances[to_acct] += dollars;
  account_balances[from_acct] -= dollars;
  /* End critical section. */
  pthread_setcancelstate(old_cancel_state, NULL);

  return 0;
}

void *thread_function(void *args) {
  int from_acc = 0;
  int to_acc = 1;
  int amount = 200;

  if (process_transaction(from_acc, to_acc, amount)) {
    printf("No existe suficientes fondos en la cuenta %d\n", from_acc);
  } else {
    printf("Se movieron %d desde la cuenta %d a la cuenta %d\n", amount,
           from_acc, to_acc);
  }

  from_acc = 1;
  to_acc = 2;
  amount = 10000;
  if (process_transaction(from_acc, to_acc, amount)) {
    printf("No existe suficientes fondos en la cuenta %d\n", from_acc);
  } else {
    printf("Se movieron %d desde la cuenta %d a la cuenta %d\n", amount,
           from_acc, to_acc);
  }

  return 0;
}

int main() {
  pthread_t thread_id;

  pthread_create(&thread_id, NULL, &thread_function, NULL);
  pthread_join(thread_id, NULL);

  return 0;
}
