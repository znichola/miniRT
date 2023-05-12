/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:18:20 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/12 12:24:06 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <math.h>
# include <float.h>

# include "mlx.h"
# include "libft.h"

# include "minirt_control_enums.h"
# include "minirt_defines.h"
# include "minirt_render.h"
# include "minirt_structs.h"
# include "minirt_render.h"
# include "minirt_ui.h"
# include "minirt_colour_defs.h"
# include "minirt_maths.h"
# include "minirt_utils.h"
# include "minirt_primitives.h"
# include "minirt_getters.h"
# include "parsing.h"

void	load_texture(t_app	*app, t_img_data *texture);
t_v3	get_pix_from_checkerboard(t_v2f point);
t_v3	get_pix_from_texture(t_img_data *texture, t_v2f point);
void	load_all_textures(t_app *a);

#endif
