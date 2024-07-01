!! NEW !!

t_list line_element;

- line cut in pieces on ' '
- between "" is one node, but variables get expanded
- between '' is one note with literal content of line



// t_sig_arg	**sig_args // single list
// {
// 	{
// 		t_cmd	**cmd // first command: ls -> -a -> -l
// 	}
// 	{
// 		t_cmd	**cmd // second command: pipe
// 	}
// 	{
// 		t_cmd	**cmd // third command: cat -> -e
// 	}
// }

// t_sig_arg	**sig_args // single list
// {
// 	{
// 		t_cmd	**cmd // first command: export -> envar
// 	}
// }

// t_sig_arg	**sig_args // single list
// {
// 	{
// 		t_cmd	**cmd // first command: redirect -> file
// 	}
// 	{
// 		t_cmd	**cmd // second command: cat -> -e
// 	}
// 	{
// 		t_cmd	**cmd // second command: pipe
// 	}
// 	{
// 		t_cmd	**cmd // third command: cat
// 	}
// 	{
// 		t_cmd	**cmd // first command: redirect -> file
// 	}
// }


// TODO:

// - Separate line in lists
// - do some syntax checking

// token == NULL
// cmd_arr == NULL

// COMMANDS:

// - "cat" access
// - "dc" builtin

// EXPANDABLES:

// - "$?" last exit status
// - "$KEY" envariable

// ACTIONS:

// - "|" pipe
// - "< > << >>" redirections

// HANDLE:

// - single quotes: literal
// - double quotes: counts as one name (for split names)

