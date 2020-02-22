#ifndef __GL_H___
#define __GL_H___

typedef struct s_list {
	void *content;
	size_t content_size;
	struct s_list *next;
} t_list;

#ifndef FT_STDIN
#define FT_STDIN 0
#endif /* !FT_STDIN */

#ifndef FT_STDOUT
#define FT_STDOUT 1
#endif /* !FT_STDOUT */

#ifndef FT_STDERR
#define FT_STDERR 2
#endif /* !FT_STDERR */

int gl(const int, char **);

#endif /* !__GL_H___ */
