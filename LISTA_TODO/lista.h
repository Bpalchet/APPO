/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lista.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpalchet <bpalchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:13:59 by bpalchet          #+#    #+#             */
/*   Updated: 2025/02/28 12:52:01 by bpalchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTA_H
 #define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_task
{
	char	*description;
	struct s_task	*next;
}t_task;

t_task	*create_task(char *description);
void	add_task(t_task **head, char *description);
void	print_tasks(t_task *head);
void	remove_task(t_task **head, char *description);
void	free_tasks(t_task *head);

#endif

