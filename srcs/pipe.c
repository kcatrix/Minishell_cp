/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exostiv <exostiv@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:18:41 by kevyn             #+#    #+#             */
/*   Updated: 2022/09/19 07:56:16 by exostiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	strlen_pipe(char *line)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (line[i])
	{
		if (line[i] == '|')
			y++;
		i++;
	}
	return (y);
}

void	ft_pipe(void)
{
	if (g_stock.nbpip > 0 && g_stock.nbpassage <= g_stock.nbpip)
	{
		if (g_stock.out != 1)
			dup2(g_stock.out, STDOUT_FILENO);
		else
			dup2(g_stock.pip[1], STDOUT_FILENO);
	}
}

void	cmd_cd_boucle(char **unparun)
{
	int	i;

	i = 0;
	while (unparun[i])
	{
		g_stock.old = i;
		if (strcmp(unparun[i], ".") == 0)
			cmd_cd_dot();
		else if (strcmp(unparun[i], "..") == 0)
			cmd_cd_dot_dot();
		else
			cmd_cd_absolute_redirect(unparun[i]);
		i++;
	}
}

void free_protect(char *str)
{
    if (str)
        free(str);
}