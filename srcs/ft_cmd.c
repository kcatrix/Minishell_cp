/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevyn <kevyn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:38:47 by tnicoue           #+#    #+#             */
/*   Updated: 2022/09/21 14:17:44 by kevyn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_spli(char **spli)
{
	int	i;

	i = 0;
	while (spli[i])
	{
		free(spli[i]);
		i++;
	}
	free(spli);
}

char	**ft_cp_env(char **env)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	while (env[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		tmp[i] = malloc(sizeof(char) * ft_strlen(env[i]) + 1);
		j = 0;
		while (env[i][j])
		{
			tmp[i][j] = env[i][j];
			j++;
		}
		tmp[i][j] = '\0';
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

char	**cmd_unset(char **spli, char **env)
{
	int		i;
	char	**tmp;

	i = 0;
	if (ft_verifexistunset(env, spli) == 1)
		return (env);
	tmp = ft_cp_env(env);
	cmd_unset2(spli, tmp, env, i);
	free_spli(tmp);
	return (env);
}

int	ft_redirect(char **spli)
{
	if (ft_strcmp(spli[0], "unset") == 0)
	{
		if (!spli[1])
			return (0);
		g_stock.cpenv = cmd_unset(spli, g_stock.cpenv);
		g_stock.cpexp = cmd_unset(spli, g_stock.cpexp);
		return (0);
	}
	else if (ft_strcmp(spli[0], "echo") == 0)
	{
		cmd_echo(spli);
		return (0);
	}
	else if (ft_strcmp(spli[0], "cd") == 0)
	{
		cmd_cd(spli);
		return (0);
	}
	if (ft_redirect_2(spli) == 0)
	{
		g_stock.end = 0;
		return (0);
	}
	return (1);
}

int	ft_cmd(char *line, char **env)
{
	char	**path;
	char	**spli;
	int		i;

	i = 0;
	init_var_cmd(line);
	if (!line || !ft_strlen(line))
		return(0);
	if (verif_space(g_stock.line2[g_stock.nbpassage]) 
		== 0 || g_stock.line2[g_stock.nbpassage] == 0)
		return (0);
	if (ft_strncmp(g_stock.line2[g_stock.nbpassage], "echo", 4) != 0)
		del_quote(g_stock.line2[g_stock.nbpassage]);
	path = path_fct(g_stock.cpenv);
	spli = ft_split(g_stock.line2[g_stock.nbpassage], ' ');
	spli = parse(spli);
	g_stock.nbpassage++;
	if (spli[0] == NULL)
		return (0);
	ft_verif_chevron(spli);
	if (ft_parse_cmd(spli, path) == 0)
	{
		if(spli)
			free_spli(spli);
		return (0);
	}
	i = verif_exist(path, spli[0]);
	if (last_check(i, path, spli[0], spli) == -1)
		return (-1);
	ft_exec(spli, path, env, i);
	g_stock.end = 0;
	return (0);
}
 