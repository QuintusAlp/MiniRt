/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 03:47:30 by qalpesse          #+#    #+#             */
/*   Updated: 2025/04/21 16:58:28 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float	closest_intersection(t_scene *scene, t_object **obj)
{
	t_solutions	s;
	t_solutions	s_buff;
	t_object	*object;

	(void)obj;
	s.s1 = INFINITY;
	s.s2 = INFINITY;
	s.s_count = 0;
	object = scene->objects;
	while (object)
	{
		s_buff = object->get_intersections(scene->primary, object);
		if (s_buff.s_count != 0)
		{
			if ((s_buff.s1 > 0 && s_buff.s1 < s.s1 && s_buff.s1 < s.s2)
				|| (s_buff.s2 > 0 && s_buff.s2 < s.s1 && s_buff.s2 < s.s2))
			{
				*obj = object;
				s = s_buff;
			}
		}
		object = object->next;
	}
	return (find_hit(s));
}

int	intersect_light(t_ray light_v, t_scene *scene)
{
	t_solutions	s;
	t_object	*object;
	float		light_dist;

	light_dist = tuple_distance(light_v.origin, scene->light->origin);
	object = scene->objects;
	while (object)
	{
		s = object->get_intersections(light_v, object);
		if (s.s_count > 0)
		{
			if ((s.s1 > 0.001f && s.s1 < light_dist) || (s.s2 > 0.001f
					&& s.s2 < light_dist))
				return (1);
		}
		object = object->next;
	}
	return (0);
}
