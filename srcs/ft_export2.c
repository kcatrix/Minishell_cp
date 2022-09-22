/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exostiv <exostiv@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:03:32 by kevyn             #+#    #+#             */
/*   Updated: 2022/09/19 08:09:44 by exostiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_export(char **spli)
{
	int	i;

	i = 0;
	if (g_stock.out != 0)
		dup2(g_stock.out, STDOUT_FILENO);
	if (g_stock.in != 1)
		dup2(g_stock.in, STDIN_FILENO);
	if (!spli[1])
		ft_export_noarg();
	else
	{	
		if (ft_parseexport(spli[1]) == 1)
		{
			return ;
		}
		else if (ft_verifenv(spli[1]) == 1)
		{
			return ;
		}
		ft_exportadd(i, spli[1]);
	}
	fix_out_inr_redir();
}

void	ft_exptoenv(char *spli)
{
	char	**cpcpenv;
	int		i;

	i = 0;
	cpcpenv = ft_exptoenv2();
	while (cpcpenv[i])
	{
		g_stock.cpenv[i] = ft_mallocex(cpcpenv[i], g_stock.cpenv[i]);
		if(cpcpenv[i])
			free(cpcpenv[i]);
		i++;
	}
	g_stock.cpenv[i] = ft_mallocex(spli, g_stock.cpenv[i]);
	g_stock.cpenv[i + 1] = NULL;
	if(cpcpenv)
		free(cpcpenv);
	return ;
}

int	ft_verifspli(char *spli)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (spli[i])
	{
		if (spli[i] == '=')
		{
			y = 1;
			while (spli[++i])
			{
				if (spli[i] != 22 && spli[i] != '\0')
					y = 1;
			}
		}
		i++;
	}
	return (y);
}

int	ft_verifdoublon(char *spli)
{
	int		i;
	char	*prespli;
	char	*preexp;
	
	i = 0;
	while (g_stock.cpexp[i])
	{
		prespli = ft_preline(spli);
		preexp = ft_preline(g_stock.cpexp[i]);
		if (strcmp(prespli, preexp) == 0)
		{
			printf("doublon\n");
			if (ft_verifspli(spli) != 0)
				g_stock.cpexp[i] = ft_mallocex(spli, g_stock.cpexp[i]);
			free(prespli);
			free(preexp);
			return (0);
		}
		free(prespli);
		free(preexp);
		i++;
	}
	printf("doublonno\n");
	return (1);
}

char	*ft_mallocex(char *str, char *str2)
{
	int	i;

	i = 0;
	if (!str || !ft_strlen(str))
		return (NULL);
	str2 = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		str2[i] = str[i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}
