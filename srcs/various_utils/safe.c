/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:50:29 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/21 17:47:25 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	*safe_malloc(size_t bytes)
{
	void	*result;

	result = malloc(bytes);
	if (result == NULL)
		error_exit("Malloc failure");
	return (result);
}
