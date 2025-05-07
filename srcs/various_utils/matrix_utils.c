/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:42:13 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/24 13:25:29 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	init_zero_matrix(float **m, int row, int col)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < row)
	{
		j = 0;
		while (j < col)
		{
			m[i][j] = 0.0f;
			j++;
		}
		i++;
	}
}

void	init_identity_matrix(float **m, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (i == j)
				m[i][j] = 1;
			else
				m[i][j] = 0;
			j++;
		}
		i++;
	}
}

float	**allocate_matrix(int cols, int rows)
{
	float	**result;
	int		i;

	i = 0;
	result = safe_malloc(rows * sizeof(float *));
	while (i < rows)
	{
		result[i] = safe_malloc(cols * sizeof(float));
		i++;
	}
	return (result);
}

t_matrix	multiply_matrixes(t_matrix m1, t_matrix m2)
{
	t_matrix	res;
	int			i;
	int			j;
	int			k;

	if (m1.nbr_col != m2.nbr_row)
		error_exit("Matrix multiplication is not possible: \
			nbr of cols of m1 must be equal to nbr of rows of m2");
	i = -1;
	init_matrix(&res, m1.nbr_row, m2.nbr_col);
	init_zero_matrix(res.m, res.nbr_row, res.nbr_col);
	while (++i < m1.nbr_row)
	{
		j = -1;
		while (++j < m2.nbr_col)
		{
			k = -1;
			while (++k < m1.nbr_col)
				res.m[i][j] += m1.m[i][k] * m2.m[k][j];
		}
	}
	return (res);
}

void	init_matrix(t_matrix *m, int nbr_row, int nbr_col)
{
	m->nbr_col = nbr_col;
	m->nbr_row = nbr_row;
	if (nbr_col == nbr_row)
		m->square = 1;
	else
		m->square = 0;
	m->m = allocate_matrix(nbr_col, nbr_row);
}
