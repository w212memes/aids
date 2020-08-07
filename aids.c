/*
 implementation of mach_aids by @IanWhiskey of Goggle's Project -1
 aids > mach_aids because of reliability
 */
 
mach_task_t get_tfp0() {
  LOG("making port");
  mach_task_t *fake_tfp0 = mach_new_port(-1);
  /* corrupt it */
  LOG("corrupting port");
  while (!corrupt(&fake_tfp0)) {
    MACH_send(&fake_tfp0, 0xe7e7e7e7, 0x0); // fake get kernel task port
  }
  /* check port */
  LOG("checking port");
  if (MACH_is_task_for_port(&fake_tfp0, 0)) {
    /* got tfp0! enjoy! */
    LOG("got tfp0");
    return &fake_tfp0;
  else
    LOG("failed. retry");
    return get_tfp0();
}

int main(int argc, char* argv[]) {
  printf("[*] getting tfp0...\n");
  mach_task_t tfp0 = get_tfp0();
  printf("[*] task=%llx\n", tfp0);
}
