/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lista.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpalchet <bpalchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:51:20 by bpalchet          #+#    #+#             */
/*   Updated: 2025/02/28 14:56:12 by bpalchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lista.h"

// crea una nuova attività da inserire in lista
t_task	*create_task(char *description)
{
	t_task *new_task = (t_task *)malloc(sizeof(t_task));
	if (!new_task)
		return (NULL);
	new_task->description = strdup(description);
	new_task->next = NULL;
	return (new_task);
}

// aggiunge una nuova attività alla fine della lista
void add_task(t_task **head, char *description)
{
	t_task *new_task = create_task(description);
	t_task *temp;
	if (!new_task)
		return ;
	if (*head == NULL)
	{
		*head = new_task;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_task;
}

// stampa la lista
void	print_tasks(t_task *head)
{
	if(!head)
	{
		printf("Nessuna attivita' nella lista!\n");
		return ;
	}
	printf("TO-DO List:\n");
	while (head)
	{
		printf ("- %s\n", head->description);
		head = head->next;
	}
}

//rimuove un'attivita' completata
void	remove_task(t_task **head, char *description)
{
	t_task	*temp = *head;
	t_task	*prev = NULL;

	while (temp && strcmp(temp->description, description) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (!temp)
	{
		printf("Attivita' non trovata!\n");
		return ;
	}
	if (!prev)
		*head = temp->next;
	else
		prev->next = temp->next;
	free(temp->description);
	free(temp);
	printf("Attivita' '%s' completata e rimossa!\n", description);
}

//libera la memoria della lista
void	free_tasks(t_task *head)
{
	t_task	*temp;
	while (head)
	{
		temp = head;
		head = head->next;
		free (temp->description);
		free(temp);
	}
}

int	main(void)
{
	t_task	*task_list = NULL;
	
	add_task(&task_list, "Fare la spesa");
	add_task(&task_list, "Lavare la macchina");
	add_task(&task_list, "Fare una corsa");
	add_task(&task_list, "Andare al 42 Firenze");
	print_tasks(task_list);
	remove_task(&task_list, "Fare una corsa");
	print_tasks(task_list);
	free_tasks(task_list);
	return (0);
}