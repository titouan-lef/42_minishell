/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:18:21 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/09 11:26:52 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	expand(t_token *token, char **env_local)
{
	expand_env_var(token, env_local);
	remove_quotes(token);
	
}