/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:00:14 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/21 16:17:36 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_H
# define KEYCODES_H

# ifdef __APPLE__
#  define ESC 53
#  define UP 126
#  define DOWN 125
#  define LEFT 123
#  define RIGHT 124
#  define PLUS 69 // on the numeric keypad
#  define MINUS 78
#  define ON_MOUSEDOWN 4   // when clicking mouse button
#  define FORWARD 119      // W
#  define BACKWARD 115     // S
#  define ROTATION_ANTI 97 // A
#  define ROTATION 100     // D
#  define KEY_PRESS 0
# else
#  define ESC 65307

#  define UP 65362
#  define DOWN 65364
#  define LEFT 65361
#  define RIGHT 65363
#  define FORWARD 119      // W
#  define BACKWARD 115     // S
#  define ROTATION_ANTI 97 // A
#  define ROTATION 100     // D

#  define PLUS 65451
#  define MINUS 65453
# endif

# define LEFT_CLICK 1
# define KEY_PRESS 2
# define RIGHT_CLICK 3
# define SCROLL_UP 4     // Scroll up
# define SCROLL_DOWN 5   // Scroll down
# define MOUSE_MOVE 6    // Mouse motion (MotionNotify)
# define REDRAW 12       // Redraw event (on expose)
# define CLOSE_WINDOW 17 // Close window event (clicking the 'X')

#endif
