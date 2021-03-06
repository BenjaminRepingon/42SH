/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 13:44:39 by smakroum          #+#    #+#             */
/*   Updated: 2014/03/27 19:38:10 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		print_error_pid(char *str)
{
	if (g_handler.cmd == 1)
		error("42sh: no such file or directory: %s\n", str);
}

void		resolve_tree(t_ast *tree, int pfd_old[2])
{
	int			status;
	int			pid;
	int			ind;

	pid = 0;
	if (tree && tree->tk->value)
	{
		if ((ind = ft_ind_op(tree->tk->value)) != -1)
			pid = g_handler.tab_op[ind](tree, pfd_old);
		else
			pid = execute(tree->tk->value, NULL, NULL, 0);
		waitpid(pid, &status, 0);
		turn_on(g_handler.term);
		if (tree->tk->prio == 0)
			g_handler.cmd = WEXITSTATUS(status);
		print_error_pid(tree->tk->value);
	}
}

void		ft_add_node(t_ast **tree, t_token *tk)
{
	*tree = (t_ast *)ft_memalloc(sizeof(t_ast));
	if (*tree)
	{
		(*tree)->tk = tk;
		(*tree)->left = NULL;
		(*tree)->right = NULL;
	}
}

t_token		*ft_lstsub(t_token *start_tk, t_token *tmp_t)
{
	t_token		*new_lst;

	new_lst = start_tk;
	while (start_tk && start_tk->next != tmp_t)
		start_tk = start_tk->next;
	if (start_tk)
		start_tk->next = NULL;
	return (new_lst);
}

void		fill_tree(t_token *tk, t_ast **tree)
{
	t_token		*tmp_t;
	t_token		*start_tk;
	t_token		*left;
	t_token		*right;

	tmp_t = tk;
	start_tk = tk;
	while (tk)
	{
		if (tk->prio > tmp_t->prio)
			tmp_t = tk;
		tk = tk->next;
	}
	if (tmp_t)
		ft_add_node(tree, tmp_t);
	right = (tmp_t) ? tmp_t->next : tmp_t;
	left = ft_lstsub(start_tk, tmp_t);
	if (start_tk != tmp_t)
		fill_tree(left, &(*tree)->left);
	if (right)
		fill_tree(right, &(*tree)->right);
}
