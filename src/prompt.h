#ifndef PROMPT_H
#define PROMPT_H

/**
 * Linux has a maximum filename length of 255 characters for most filesystems
 * (including EXT4), and a maximum path of 4096 characters.
 */
# define PROMPT_BUF_SIZE 4096

void prompt(void);

#endif
