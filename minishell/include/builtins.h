/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:19:57 by lguerbig          #+#    #+#             */
/*   Updated: 2024/12/17 16:09:52 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <stdlib.h>
# include <linux/limits.h>
# include "libft.h"

/*---structures---*/
typedef struct s_mshd
{
	char	**env_local;
	char	**env_export;
}				t_mshd;

/*---funtions---*/
void	echo(char **str, char **env_local);
void	pwd(char **str, char **env_local);
void	export(char **str, char **env_local, char **env_export);

#endif