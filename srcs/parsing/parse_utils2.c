/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:14:50 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/22 15:46:42 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	split_len(char **spl)
{
	int	i;

	i = 0;
	if (!spl)
		return (i);
	while (spl[i] && spl[i][0] != '\n')
		i++;
	return (i);
}

int	check_args_number(int nbr, char **buffer)
{
	int	len;

	len = split_len(buffer);
	if (len > nbr || len < nbr)
		return (1);
	else
		return (0);
}

t_matrix	create_identity_matrix(int size)
{
	t_matrix	m;

	init_matrix(&m, size, size);
	init_identity_matrix(m.m, m.nbr_col);
	return (m);
}

void	ft_object_addback(t_object **objects, t_object *new_object)
{
	t_object	*temp;

	new_object->next = NULL;
	if (!objects)
		return ;
	temp = *objects;
	if (!(*objects))
	{
		*objects = new_object;
		return ;
	}
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = new_object;
}
