#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
    Main architecture:
        shell_loop:
            shell_readline():
                dumduz satirlari okuyacaksin
            shell_splitline():
                splitleme sirasi:
                    ; -> | (pipe) -> _ (space ch)
        built in commands:
            quit (shellden cikmak icin (eger arkaplanda calismaya devam eden bir komut varsa onun cikti vermesini bekler))

*/
/*
    adim 1) hocalarin istedikleri system callari arastirin
    adim 2) projenin mimarisini olustur, (hangi asamada hangi fonksiyon cagiralacak falan) 
    adim 3) kodluyoruz
 */
void shell_loop(void)
{
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = lsh_read_line();
    args = lsh_split_line(line);
    status = lsh_execute(args);

    free(line);
    free(args);
    fflush(stdout); // dokumandan 
  } while (status);
}

int main(int argc, char **argv)
{
  // Load config files, if any.

  // Run command loop.
  shell_loop();

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}
