/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:19:57 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/28 21:45:30 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "execution.h"

/*---funtions---*/
int		echo(char **cmd);
int		env(char **cmd, char **env);
char	*get_cwd(char **env);
int		pwd(char **env);
int		cd(char **cmd, char **env);
int		unset(char **cmd, char ***env);
void	my_exit(char **cmd, t_data *data, int is_piped);

#endif