/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:43:12 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/07/01 19:21:45 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_types.h"

int	main(void)
{
	t_list		**element_head;
	t_token_node	**sig_head;

	// set up two command lists, and add them to the significant argument list
	lstadd_back((void **)element_head, getnext_string, new_node_string("export")); // command export
	lstadd_back((void **)element_head, getnext_string, new_node_string("HELLO=Hello world!"));	// parameter HELLO=Hello world!
	lstadd_back((void **)sig_head, getnext_token, new_node_sig_arg(element_head, NULL, T_COMMAND)); // significant argument "export HELLO=Hello world!"
	lstadd_back((void **)element_head, getnext_string, new_node_string("echo")); // command echo
	lstadd_back((void **)element_head, getnext_string, new_node_string("$HELLO")); // parameter $HELLO
	lstadd_back((void **)sig_head, getnext_token, new_node_sig_arg(element_head, NULL, T_COMMAND)); // significant argument "echo $HELLO"
	TEST_print_lst((void **)element_head, getnext_string);
	TEST_print_lst((void **)sig_head, getnext_token);
	lstfree((void **)element_head, getnext_string);
	TEST_print_lst((void **)element_head, getnext_string);
	TEST_print_lst((void **)sig_head, getnext_token);
}