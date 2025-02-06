/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:52:42 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/06 15:10:27 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include <fcntl.h>
# include "utils.h"

typedef struct s_here_doc
{
	char	*filename;
	char	*limiter;
}	t_here_doc;

int		read_here_docs(t_data *data);

/*---utils---*/
char	*generate_random_string(size_t length);
int		fill_here_doc_lst(char **redirs, t_list **here_docs);
void	clear_here_docs(t_list *here_docs);

#endif