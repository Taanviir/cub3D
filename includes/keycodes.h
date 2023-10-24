/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:50:08 by tanas             #+#    #+#             */
/*   Updated: 2023/10/23 16:44:14 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_H
#define KEYCODES_H

#ifdef __APPLE__
#define ESCAPE 53
#endif

#ifdef __LINUX__
#define ESCAPE XK_Escape
#endif

#endif
