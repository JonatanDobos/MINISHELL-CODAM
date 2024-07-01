#include "../minishell.h"

int	readline_loop(void)
{
	char	*line;
	int		hindex;
	HIST_ENTRY	*hisentry;
	HISTORY_STATE	*hisstate;

	while (true)
	{
		line = readline("minishell > ");
		if (!line || !ft_strncmp(line, "exit", 5))
			return (free(line), 0);
		add_history(line);
		if (ft_strlen(line) >= 6 && !ft_strncmp(line, "hget ", 5) && ft_isdigit(line[5]))
		{
			hindex = ft_atoi(line + 5);
			hisstate = history_get_history_state();
			if (hisstate->length >= hindex)
			{
				hisentry = history_get(2);
				printf("history[%i]: %s\n", hindex, hisentry->line);
			}
			else
				printf("history[entry doesn't exist!] >> first entry: %i\n", hisstate->length + 1);
		}
		if (!ft_strncmp(line, "print: ", 7))
			printf("%s\n", line + 7);
		free(line);
	}
	return (1);
}

int	main(void)
{
	printf("START\n");
	printf("RET: %i\n", readline_loop());
	printf("END\n");
}
