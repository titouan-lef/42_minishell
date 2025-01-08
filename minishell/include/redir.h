/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:40:18 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/08 17:43:59 by lguerbig         ###   ########.fr       */
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
}			t_redir_name;

/*---redirection.c---*/
int		redirect_input(int fd, char *file_name);
int		redirect_output(int fd, char *file_name);
int		redirect_output_append_mode(int fd, char *file_name);
void	get_here_doc_input(int file, char *limit);
int		here_doc(int fd, char *limit);

#endif