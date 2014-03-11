/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 18:14:38 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/11 14:33:41 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_getenv(const char *name)
{
	int				i;
	int				lenth;
	char			*tmp;

	i = 0;
	tmp = ft_strjoin(name, "=");
	while (environ[i] && ft_strncmp(environ[i], tmp, ft_strlen(tmp)))
		i++;
	if (environ[i])
	{
		lenth = ft_strlen(tmp);
		ft_strdel(&tmp);
		return (&environ[i][lenth]);
	}
	else
	{
		lenth = ft_strlen(tmp);
		write(2, tmp, (lenth - 1));
		ft_strdel(&tmp);
		ft_putendl_fd(": not found", 2);
		return (NULL);
	}
}
