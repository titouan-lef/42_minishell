/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:40:18 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/05 17:40:45 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "commands.h"

typedef enum e_redir_name
{
	INPUT,
	HERE_DOC,
	OUTPUT,
	OUTPUT_APPEND,
	ERROR,
}			t_redir_name;

/*---random.c---*/
char		*generate_random_string(size_t length);

/*---redirection.c---*/
int			redirect_input(int fd, char *file_name);
int			redirect_output(int fd, char *file_name);
int			redirect_output_append_mode(int fd, char *file_name);
int			redirect_here_doc(int fd, char *limit, t_list *here_docs);
int			redir_manager(char **redirs, t_list *here_docs);

/*---here_doc---*/
int			fill_here_doc_lst(char **redirs, t_list **here_docs);
int			read_here_docs(t_data *data);
void		clear_here_docs(t_list *here_docs);

#endif