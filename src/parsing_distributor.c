/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_distributor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:47:47 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/08 23:20:04 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// Returns: false when reprompt is needed (e.g. on syntax error)
bool	parsing_distributor(t_shell *shell)
{
	parse_pre(shell, shell->line);
	// if (shell->print_info)// TEST
	// 	TEST_print_elem_list(shell, C_TEAL, true, "Line Element firstcheck");// TEST
	if (shell->line_element_head == NULL)
		return (false);
	tokenize(shell);
	parse_post(shell);
	all_heredocs(shell);
	return (true);
}
