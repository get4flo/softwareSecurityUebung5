
int main(void)

{
  long lVar1;
  int iVar2;
  long in_FS_OFFSET;
  char buf [2];
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  setup();
  puts("Hello and welcome to my new experimental Fotispy app !");
  puts("(We are still in the alpha phase so many things may not b e implemented!");
  puts("====================================== ===============");
  do {
    menu();
    getsn(buf,2);
    iVar2 = atoi(buf);
    switch(iVar2) {
    case 0:
      puts("Bye bye");
      if (lVar1 == *(long *)(in_FS_OFFSET + 0x28)) {
        return 0;
      }
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail();
    case 1:
      reg();
      break;
    case 2:
      add_song();
      break;
    case 3:
      edit_comment();
      break;
    case 4:
      delete_song();
      break;
    case 5:
      like_song();
      break;
    case 6:
      show_stats();
      break;
    case 7:
      edit_stats();
      break;
    case 8:
      secret_malloc();
    }
  } while( true );
}

void setup(void)

{
  setvbuf(stdin,(char *)0x0,2,0);
  setvbuf(stdout,(char *)0x0,2,0);
  setvbuf(stderr,(char *)0x0,2,0);
  return;
}



/* WARNING: Unknown calling convention -- yet parameter s torage is locked */

void menu(void)

{
  puts("[0] Exit");
  puts("[1] Create User");
  puts("[2] Add song");
  puts("[3] Edit comment");
  puts("[4] Delete Song");
  puts("[5] Grade a song");
  puts("[6] Show stats");
  puts("[7] Edit stats");
  printf("[~] Choice: ");
  return;
}


uint32_t getsn(char *buf,ssize_t len)

{
  int iVar1;
  ssize_t len_local;
  char *buf_local;
  char c;
  int i;
  
  i = 0;
  do {
    if (len <= i) break;
    iVar1 = _IO_getc(stdin);
    c = (char)iVar1;
    iVar1 = i + 1;
    buf[i] = c;
    i = iVar1;
  } while (c != '\n');
  while (c != '\n') {
    iVar1 = _IO_getc(stdin);
    c = (char)iVar1;
  }
  if (i != len) {
    i = i - 1;
    buf[i] = '\0';
  }
  return i;
}


/* WARNING: Unknown calling convention -- yet parameter s torage is locked */

void reg(void)

{
  printf("[~] Username: ");
  getsn(cur.name,0x20);
  printf("[~] Password: ");
  getsn(cur.pass,0x20);
  return;
}


/* WARNING: Unknown calling convention -- yet parameter s torage is locked */

void add_song(void)

{
  long lVar1;
  uint uVar2;
  song *psVar3;
  long in_FS_OFFSET;
  int idx;
  uint32_t comment_size;
  char tmp [8];
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  for (idx = 0; (idx < 0x21 && (cur.songs[idx] != (song *)0x0)) ; idx = idx + 1) {
  }
  if (idx == 0x20) {
    puts("[-] No free songs left");
  }
  else {
    tmp[0] = '\0';
    tmp[1] = '\0';
    tmp[2] = '\0';
    tmp[3] = '\0';
    tmp[4] = '\0';
    tmp[5] = '\0';
    tmp[6] = '\0';
    tmp[7] = '\0';
    printf("[~] How long will the comment be: ");
    getsn(tmp,8);
    uVar2 = atoi(tmp);
    if (uVar2 == 0) {
      puts("[-] Please enter a number higher than 0");
    }
    else {
      psVar3 = (song *)malloc((ulong)(uVar2 + 8));
      cur.songs[idx] = psVar3;
      printf("[~] Enter the comment: ");
      getsn((char *)(cur.songs[idx] + 1),(ulong)uVar2);
    }
  }
  if (lVar1 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* WARNING: Unknown calling convention -- yet parameter s torage is locked */

void edit_comment(void)

{
  long lVar1;
  int8_t iVar2;
  uint uVar3;
  long in_FS_OFFSET;
  int8_t idx;
  uint32_t comment_size;
  char tmp [8];
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  iVar2 = get_idx();
  if (-1 < iVar2) {
    tmp[0] = '\0';
    tmp[1] = '\0';
    tmp[2] = '\0';
    tmp[3] = '\0';
    tmp[4] = '\0';
    tmp[5] = '\0';
    tmp[6] = '\0';
    tmp[7] = '\0';
    printf("[~] How long will the new comment be: ");
    getsn(tmp,8);
    uVar3 = atoi(tmp);
    if (uVar3 == 0) {
      puts("[-] Please enter a number higher than 0");
    }
    else {
      printf("[~] Enter the new comment: ");
      getsn((char *)(cur.songs[(int)iVar2] + 1),(ulong)uVar3);
    }
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


/* WARNING: Unknown calling convention */

int8_t get_idx(void)

{
  long lVar1;
  byte bVar2;
  uint uVar3;
  long in_FS_OFFSET;
  uint8_t idx;
  char tmp [2];
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  tmp[0] = '\0';
  tmp[1] = '\0';
  printf("[~] Which song to you want to select: ");
  getsn(tmp,2);
  uVar3 = atoi(tmp);
  bVar2 = (byte)uVar3;
  if ((0x1f < bVar2) || (cur.songs[(int)(uVar3 & 0xff)] == (song *)0x0)) {
    puts("[-] Invalid song idx");
    bVar2 = 0xff;
  }
  if (lVar1 == *(long *)(in_FS_OFFSET + 0x28)) {
    return bVar2;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* WARNING: Unknown calling convention -- yet parameter s torage is locked */

void delete_song(void)

{
  int8_t iVar1;
  int8_t idx;
  
  iVar1 = get_idx();
  if (-1 < iVar1) {
    free(cur.songs[(int)iVar1]);
  }
  return;
}


/* WARNING: Unknown calling convention -- yet parameter s torage is locked */

void like_song(void)

{
  long lVar1;
  int8_t iVar2;
  long in_FS_OFFSET;
  int8_t idx;
  char tmp [2];
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  iVar2 = get_idx();
  if (-1 < iVar2) {
    printf("[~] Was the song [g]ood or [b]ad: ");
    tmp[0] = '\0';
    tmp[1] = '\0';
    getsn(tmp,1);
    if (tmp[0] == 'b') {
      cur.songs[(int)iVar2]->dislikes = cur.songs[(int)iVar2]->disl ikes + '\x01';
    }
    else {
      cur.songs[(int)iVar2]->likes = cur.songs[(int)iVar2]->likes + '\x01';
    }
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


/* WARNING: Unknown calling convention -- yet parameter s torage is locked */

void show_stats(void)

{
  int8_t iVar1;
  int8_t idx;
  
  iVar1 = get_idx();
  if (-1 < iVar1) {
    printf("[+] You Song has %d likes\n",(ulong)cur.songs[(int)i Var1]->likes);
    printf("[+] You Song has %d dislikes\n",(ulong)cur.songs[(in t)iVar1]->dislikes);
    printf("[+] You Song is %d seconds long\n",(ulong)cur.song s[(int)iVar1]->len);
    puts("[!] The rest has not been implemented yet");
  }
  return;
}


/* WARNING: Unknown calling convention -- yet parameter s torage is locked */

void edit_stats(void)

{
  long lVar1;
  song *psVar2;
  char cVar3;
  int8_t iVar4;
  int iVar5;
  long in_FS_OFFSET;
  int8_t idx;
  char c;
  char tmp [3];
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  iVar4 = get_idx();
  if (-1 < iVar4) {
    puts("[~] What do you want to change?");
    puts("[l]ikes");
    puts("[d]islikes");
    puts("length in [s]econds");
    printf("[~] Choice: ");
    tmp[0] = '\0';
    tmp[1] = '\0';
    tmp[2] = '\0';
    getsn(tmp,2);
    cVar3 = tmp[0];
    printf("[~] What is the new value [0-255]: ");
    getsn(tmp,3);
    if (cVar3 == 'l') {
      psVar2 = cur.songs[(int)iVar4];
      iVar5 = atoi(tmp);
      psVar2->likes = (uint8_t)iVar5;
    }
    else if (cVar3 == 'd') {
      psVar2 = cur.songs[(int)iVar4];
      iVar5 = atoi(tmp);
      psVar2->dislikes = (uint8_t)iVar5;
    }
    else if (cVar3 == 's') {
      psVar2 = cur.songs[(int)iVar4];
      iVar5 = atoi(tmp);
      psVar2->len = (uint8_t)iVar5;
    }
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


/* WARNING: Unknown calling convention -- yet parameter s torage is locked */

void secret_malloc(void)

{
  char *sh;
  
  malloc(0x101614);
  return;
}




