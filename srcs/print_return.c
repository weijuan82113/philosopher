/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_return.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:02:54 by wchen             #+#    #+#             */
/*   Updated: 2023/02/23 00:01:12 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *printf_return(char *print_str, void *ret)
{
	printf("%s", print_str);
	return (ret);
}
