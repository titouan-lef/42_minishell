/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:52:42 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/12 15:42:22 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include <fcntl.h>
# include "utils.h"

int		read_here_doc(char *limiter, char **filename, t_data *data);

/*---utils---*/
char	*generate_random_string(size_t length);
int		fill_here_doc_lst(char **redirs, t_data *data, int *i);
void	clear_here_docs(t_list *here_docs);

#endif