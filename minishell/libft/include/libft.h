/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:04:11 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/17 15:26:35 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "print.h"
# include "get_next_line.h"
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* char */
int		ft_islower(int c);
int		ft_isupper(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);

/* collection */
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstremove_front(t_list *lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* compare */
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/* convert */
int		ft_to_positive_int(const char *nptr);
int		ft_toint(int c);
int		ft_tochar(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);

/* copy */
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memdup(const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strdup(const char *s);

/* malloc */
void	ft_free_matrix(void **matrix, size_t size);
void	ft_clean_matrix(void **matrix);
void	*ft_calloc(size_t nmemb, size_t size);

/* search */
void	*ft_memchr(const void *s, int c, size_t n);
size_t	ft_strcspn(const char *s, const char *reject);
char	*ft_strchrnul(const char *s, int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);

/* sort */
void	ft_swap(int *a, int *b);
void	ft_insertion_sort(int *tab, size_t n);
void	ft_bubble_sort(int *tab, size_t n);
void	ft_selection_sort(int *tab, size_t n);
void	ft_insertion_qsort(void *tab, size_t nmemb, size_t size,
			int (*compar)(const void *, const void *));

/* stinrg */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strnjoin(const char *s1, size_t n1, const char *s2, size_t n2);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
int		ft_is_in_charset(const char *charset, char c);
char	**ft_split_charset(char const *s, char const *charset);
size_t	ft_strlen(const char *s);
size_t	ft_strnlen(const char *s, size_t n);

/* ft_fill_memory */
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);

#endif
