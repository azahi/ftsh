#ifndef __GL_H___
#define __GL_H___

typedef struct s_list {
	void *content;
	size_t content_size;
	struct s_list *next;
} t_list;

int gl(const int, char **);

#endif /* !__GL_H___ */
