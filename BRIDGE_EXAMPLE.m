t_sig_arg	**sig_args // single list
{
	{
		t_cmd	**cmd // first command: ls -> -a -> -l
	}
	{
		t_cmd	**cmd // second command: pipe
	}
	{
		t_cmd	**cmd // third command: cat -> -e
	}
}

t_sig_arg	**sig_args // single list
{
	{
		t_cmd	**cmd // first command: export -> envar
	}
}

t_sig_arg	**sig_args // single list
{
	{
		t_cmd	**cmd // first command: redirect -> file
	}
	{
		t_cmd	**cmd // second command: cat -> -e
	}
	{
		t_cmd	**cmd // second command: pipe
	}
	{
		t_cmd	**cmd // third command: cat
	}
	{
		t_cmd	**cmd // first command: redirect -> file
	}
}
