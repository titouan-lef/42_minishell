/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:42:34 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/06 16:49:55 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_EXEC_H
# define CMD_EXEC_H

# include "utils.h"

typedef enum e_redir_name
{
	INPUT,
	HERE_DOC,
	OUTPUT,
	OUTPUT_APPEND,
	ERROR,
}	t_redir_name;

/*---cmd_exec---*/
int		cmd_exec(t_data *data, t_token *token, int is_piped);

/*---builtin---*/
int		builtin_manager(char **cmd, char **redir, t_data *data, int is_piped);
int		cd(char **cmd, char **env);
int		goto_dir(char *dir, char **env);
int		echo(char **cmd);
int		env(char **cmd, char **env);
int		my_exit(char **cmd, t_data *data, int is_piped);
int		export(char **cmd, char ***env_local, char ***env_export);
char	*get_from_env(char **env, char *name);
char	*get_cwd(char **env);
int		pwd(char **env);
int		unset(char **cmd, char ***env);

/*---external cmd---*/
int	update_cmd_path(char **path, char *cmd_name, char **env);

/*---redir---*/
int	redir_manager(char **redirs, t_list *here_docs);
int	redirect_input(int fd, char *file_name);
int	redirect_output(int fd, char *file_name);
int	redirect_output_append_mode(int fd, char *file_name);
int	redirect_here_doc(int fd, char *limiter, t_list *here_docs);

#endif