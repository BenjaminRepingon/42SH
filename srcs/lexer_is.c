/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_is.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 16:16:34 by mgarcin           #+#    #+#             */
/*   Updated: 2014/03/24 17:45:45 by mgarcin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == ';' || c == '&')
		return (1);
	return (0);
}

int		is_quote(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}

int		is_alpha(char c)
{
	if (ft_isprint(c) && c != ' ' && !is_operator(c) && !is_quote(c))
		return (1);
	return (0);
}
