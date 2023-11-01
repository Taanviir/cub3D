/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:50:08 by tanas             #+#    #+#             */
/*   Updated: 2023/11/01 16:35:28 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_H
# define KEYCODES_H

# if __APPLE__
#  define KEYCODE_ESC 53
#  define KEYCODE_W 13
#  define KEYCODE_A 0
#  define KEYCODE_S 1
#  define KEYCODE_D 2
#  define KEYCODE_L_ARROW 123
#  define KEYCODE_R_ARROW 124

# elif __LINUX__
#  define KEYCODE_ESC XK_Escape
#  define KEYCODE_W 119
#  define KEYCODE_A 97
#  define KEYCODE_S 115
#  define KEYCODE_D 100
#  define KEYCODE_L_ARROW 65361
#  define KEYCODE_R_ARROW 65363

# endif

#endif