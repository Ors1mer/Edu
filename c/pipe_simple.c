/* pipe_simple.c
 * The program creates a pipe with a child process.
 * The child process writes a verse into the channel,
 * and the parent prints the verse to stdout.
 */
#include <unistd.h>
#include <stdlib.h>

const char verse[] = "To be, or not to be, that is the question:\n"
                     "Whether 'tis nobler in the mind to suffer\n"
                     "The slings and arrows of outrageous fortune,\n"
                     "Or to take Arms against a Sea of troubles,\n"
                     "And by opposing end them: to die, to sleep\n"
                     "No more; and by a sleep, to say we end\n"
                     "The heart-ache, and the thousand natural shocks\n"
                     "That Flesh is heir to? 'Tis a consummation\n"
                     "Devoutly to be wished. To die, to sleep,\n"
                     "To sleep, perchance to Dream; aye, there's the rub,\n"
                     "For in that sleep of death, what dreams may come,\n"
                     "When we have shuffled off this mortal coil,\n"
                     "Must give us pause. There's the respect\n"
                     "That makes Calamity of so long life:\n"
                     "For who would bear the Whips and Scorns of time,\n"
                     "The Oppressor's wrong, the proud man's Contumely,\n"
                     "The pangs of dispised Love, the Law’s delay,\n"
                     "The insolence of Office, and the spurns\n"
                     "That patient merit of th'unworthy takes,\n"
                     "When he himself might his Quietus make\n"
                     "With a bare Bodkin? Who would Fardels bear,\n"
                     "To grunt and sweat under a weary life,\n"
                     "But that the dread of something after death,\n"
                     "The undiscovered country, from whose bourn\n"
                     "No traveller returns, puzzles the will,\n"
                     "And makes us rather bear those ills we have,\n"
                     "Than fly to others that we know not of?\n"
                     "Thus conscience does make cowards of us all,\n"
                     "And thus the native hue of Resolution\n"
                     "Is sicklied o'er, with the pale cast of Thought,\n"
                     "And enterprises of great pitch and moment,\n"
                     "With this regard their Currents turn awry,\n"
                     "And lose the name of Action. Soft you now,\n"
                     "The fair Ophelia? Nymph, in thy Orisons\n"
                     "Be all my sins remember'd."
;

int main()
{
    char buf[3];
    int fd[2];
    int pid, cnt;
    pipe(fd);
    pid = fork();
    if(pid == 0) { /* child */
        close(fd[0]);
        write(fd[1], verse, sizeof(verse)-1);
        exit(0);
    }
    /* parent */
    close(fd[1]);
    do {
        cnt = read(fd[0], buf, sizeof(buf)-1);
        write(1, buf, cnt);
    } while(cnt > 0);
    write(1, "\n", 1);

    return 0;
}
