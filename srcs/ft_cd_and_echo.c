/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_and_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevyn <kevyn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:13:17 by kcatrix           #+#    #+#             */
/*   Updated: 2022/09/21 19:00:32 by kevyn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_echo(char **spli)
{
	int	i;

	i = 1;
	if (spli[1])
		del_quote(spli[1]);
	if (g_stock.out != 0)
		dup2(g_stock.out, STDOUT_FILENO);
	if (g_stock.in != 1)
		dup2(g_stock.in, STDIN_FILENO);
	if (!spli[1])
	{
		printf("\n");
		fix_out_inr_redir();
		return ;
	}
	if (echo_option(spli[1]) == 0)
		i++;
	while (spli[i])
	{
		printf("%s", spli[i++]);
		if (spli[i] != NULL)
			printf(" ");
	}
	if (echo_option(spli[1]) == 1)
		printf("\n");
	fix_out_inr_redir();
}

int	echo_option(char *spli)
{
	int	i;

	i = 1;
	if (spli[0] == '-')
	{
		while (spli[i])
		{
			if (spli[i] == 'n')
			{
				i++;
			}
			else
				return (1);
		}
		if (i == 1)
			return (1);
	}
	else
		return (1);
	return (0);
}

//Absolu n'est pas un absolu mais un fdp d'imposteur, 
//il est mi absolu mi relatif, il faut gérer les /./ lors d'un absolu
void	cmd_cd(char **spli)
{
	char	**unparun;

	if (spli[1])
		unparun = ft_split(spli[1], '/');
	if (!spli[1])
	{
		cmd_cd_noarg();
		return ;
	}
	if (spli[1][0] == '/')
		cmd_cd_absolute(spli[1]);
	else
	{
		cmd_cd_boucle(unparun);
	}
	if (spli[1])
		free_spli(unparun);
}

char	**cmd_cd_dot(void)
{
	int	i;

	i = 0;
	while (g_stock.cpenv[i])
	{
		if (ft_memcmp(g_stock.cpenv[i], "OLDPWD=", 7) == 0 && g_stock.old == 0)
		{
			free(g_stock.cpenv[i]);
			g_stock.cpenv[i] = "OLDPWD=";
			g_stock.cpenv[i] = ft_strjoin(g_stock.cpenv[i], getpwd());
		}
		i++;
	}
	return (NULL);
}

char	*getpwd(void)
{
	int	i;
	int	j;

	i = 0;
	j = 4;
	while (g_stock.cpenv[i])
	{
		if (ft_memcmp(g_stock.cpenv[i], "PWD=", 4) == 0)
			return (g_stock.cpenv[i] + 4);
		i++;
	}
	return (NULL);
}
