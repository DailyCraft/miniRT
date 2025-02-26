/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:27:26 by cgrasser          #+#    #+#             */
/*   Updated: 2025/02/26 22:28:20 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//TODO NORM
bool intersect_triangle(t_obj *triangle_obj, t_ray *ray, t_hit *hit)
{
    t_vec A = triangle_obj->triangle.pos1;
    t_vec B = triangle_obj->triangle.pos2;
    t_vec C = triangle_obj->triangle.pos3;

    // Calculer les vecteurs AB et AC
    t_vec AB = vec_sub(B, A);
    t_vec AC = vec_sub(C, A);

    // Calculer le produit vectoriel de la direction du rayon et le vecteur AC
    t_vec h = vec_cross(&ray->dir, &AC);

    // Calculer le déterminant
    double det = vec_dot(AB, h);

    // Si le déterminant est proche de zéro, il n'y a pas d'intersection
    if (det > -0.0001 && det < 0.0001)
        return false;

    // Calcul de l'inverse du déterminant
    double inv_det = 1.0 / det;

    // Calcul de la différence entre l'origine du rayon et le sommet A du triangle
    t_vec s = vec_sub(ray->pos, A);

    // Calcul du paramètre u
    double u = vec_dot(s, h) * inv_det;

    // Si u est en dehors de l'intervalle [0, 1], l'intersection est en dehors du triangle
    if (u < 0.0 || u > 1.0)
        return false;

    // Calcul du produit vectoriel entre s et AB
    t_vec q = vec_cross(&s, &AB);

    // Calcul du paramètre v
    double v = vec_dot(ray->dir, q) * inv_det;

    // Si v est en dehors de l'intervalle [0, 1] ou u + v > 1, l'intersection est en dehors du triangle
    if (v < 0.0 || u + v > 1.0)
        return false;

    // Calcul de t, le paramètre de l'intersection
    double t = vec_dot(AC, q) * inv_det;

    // Si t est positif, il y a une intersection
    if (t > 0.0001) {
		hit->pos = ray_at(ray, t);
       
        // Calcul de la normale du triangle
        t_vec normal = vec_cross(&AB, &AC);
		normalize(&normal);
        return true;
    }
    return false;
}

//TODO UV TRIANGLE