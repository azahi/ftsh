#include <ft.h>
#include <ft_stdlib.h>
#include <ft_string.h>
#include <unistd.h>

#include "gl.h"

#define BUFF_SIZE 8

static t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*node;

	if (!(node = malloc(sizeof(*node))))
		return (NULL);
	if (!(node->content = malloc(content_size)))
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	if (!content)
	{
		node->content = NULL;
		node->content_size = 0;
		return (node);
	}
	ft_memcpy(node->content, content, content_size);
	node->content_size = content_size;
	return (node);
}

static t_list	*get_fd(t_list **lst, int fd)
{
	t_list	*node;

	if (!*lst)
		*lst = ft_lstnew("\0", sizeof(char));
	node = *lst;
	while (node)
	{
		if (((int)node->content_size) == fd && node->content)
			return (node);
		if (!node->next)
			break ;
		node = node->next;
	}
	node->next = ft_lstnew("\0", sizeof(char));
	node->next->content_size = fd;
	return (node->next);
}

static char		*get_line(char **src)
{
	char	*str;
	char	*tmp;
	int		i;

	i = 0;
	while ((*src)[i] && (*src)[i] != '\n')
		i++;
	str = strnew(i);
	ft_strncpy(str, *src, i);
	tmp = ft_strdup(&((*src)[i]));
	free(*src);
	*src = tmp;
	if (ft_strchr(*src, '\n'))
		*src = ft_strdup(ft_strchr(*src, '\n') + 1);
	else
		*src = ft_strdup("\0");
	free(tmp);
	return (str);
}

int				gl(const int fd, char **line)
{
	char			*content_tmp;
	char			buf[BUFF_SIZE + 1];
	int				size;
	static t_list	*lst_save;
	t_list			*lst;

	if (!line || fd < 0 || BUFF_SIZE < 1)
		return (-1);
	lst = get_fd(&lst_save, fd);
	size = 0;
	while (!(ft_strchr(lst->content, '\n')) &&
		(size = read(lst->content_size, buf, BUFF_SIZE)) > 0)
	{
		buf[size] = '\0';
		content_tmp = lst->content;
		lst->content = strjoin(content_tmp, buf);
		free(content_tmp);
	}
	if (size == -1 || (!size && !ft_strlen(lst->content)))
		return (size);
	*line = get_line((char**)(&lst->content));
	return (1);
}
