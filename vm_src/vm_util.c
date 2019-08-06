/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maginist <maginist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 16:20:58 by ndelhomm          #+#    #+#             */
/*   Updated: 2019/08/06 13:40:58 by maginist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void	ft_itoo_vm(t_core *core, int pos, unsigned long long int nb
	, unsigned long long int size)
{
	unsigned long long int	i;
	unsigned long long int	div;

	i = size;
	div = 1;
	nb %= 9223372036854775807;
	while (--i > 0)
		div *= 256;
	nb %= div * 256;
	while (i < size)
	{
		core->arena[(pos + i) % MEM_SIZE] = nb / div;

		nb %= div;
		div /= 256;
		i++;
	}
}

void	del_process(t_proces **proces, int i)
{
	t_proces	*tmp;
	t_proces	*pr;
	t_proces	*prev;
	int			j;

	pr = *proces;
	j = 0;
	tmp = 0;
	prev = 0;
	if (!i)
	{
		tmp = *proces;
		ft_printf("tmp->champ = %d && i = 0\n", tmp->champ);
		*proces = (*proces)->next;
	}
	else
	{
		while (pr)
		{
			if (j == i)
			{
				tmp = pr;
				prev->next = pr->next;
				break ;
			}
			prev = pr;
			pr = pr->next;
			j++;
		}
	}
	free(tmp);
}

int		check_lives(t_core *core)
{
	t_proces	*pr;
	int			i;
	int j;

	if (!(core->proces))
		return (0);
	pr = core->proces;
	i = 0;
	while (pr && pr->next)
	{
		j = 0;
		if (pr && pr->next && !(pr->alive))
		{
			pr = pr->next;
			del_process(&core->proces, i);
			pr = core->proces;
			while (j != i && pr)
				pr = pr->next;
			core->sum_process--;
		}
		else
			pr = pr->next;
		i++;
	}
	if (core->proces)
		return (1);
	return (0);
}

void	reinit_cycle_lives(t_core *core)
{
	t_proces	*pr;
	t_champ		*champ;

	champ = core->champs;
	core->tmp_cycle = 0;
	core->nbr_live = 0;
	pr = core->proces;
	while (champ)
	{
		champ->live_by_ctd = 0;
		champ = champ->next;
	}
	while (pr)
	{
		pr->alive = 0;
		pr = pr->next;
	}
}
