/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exostiv <exostiv@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:14:19 by kcatrix           #+#    #+#             */
/*   Updated: 2022/09/19 06:11:38 by exostiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	verifline(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

/*void	ft_recup_export()
{
	recuperer le export
}*/

void	ft_env(void)
{
	int	i;

	i = 0;
	if (g_stock.out != 0)
		dup2(g_stock.out, STDOUT_FILENO);
	if (g_stock.in != 1)
		dup2(g_stock.in, STDIN_FILENO);
	while (g_stock.cpenv[i])
	{
		if (verifline(g_stock.cpenv[i]) == 0)
			printf("%s\n", g_stock.cpenv[i]);
		i++;
	}
	fix_out_inr_redir();
}
