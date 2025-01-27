/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:19:57 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/27 18:34:20 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "execution.h"

/*---funtions---*/
void	echo(char **cmd);
char	*get_cdw(char **env);
int		pwd(char **env);
int		cd(char **cmd, char **env);
int		unset(char **cmd, char ***env);
void	my_exit(char **cmd, t_data *data, int is_piped);

#endif