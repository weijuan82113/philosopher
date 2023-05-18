/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_return.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:02:54 by wchen             #+#    #+#             */
/*   Updated: 2023/03/06 00:13:14 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*printf_return(char *print_str, void *ret)
{
	printf("%s", print_str);
	return (ret);
}

int	printf_return_int(char *print_str, int ret)
{
	printf("%s", print_str);
	return (ret);
}
