/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:24:36 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/06 14:36:07 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <readline/readline.h>
# include <readline/history.h>
# include "utils.h"

char	*get_prompt(char **env);
char	*read_lines(t_data *data, int here_doc);

#endif