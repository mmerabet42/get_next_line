/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:45:38 by mmerabet          #+#    #+#             */
/*   Updated: 2017/11/12 19:44:22 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnchr(const char *a, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && a[i] != c)
		++i;
	return ((char *)(i == n ? NULL : &a[i]));
}
