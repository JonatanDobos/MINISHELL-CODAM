TODO:

- INP[chmod 000 infile && <infile cat | cat >outfile] FREEZES!
- INP[<file] EXITS MINISHELL!
- MALLOC PROTECTION!
- SIGNALS!
- WAITPD protection if killsig in cat

FIX[!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!]
->
	minishell > echo <<l | cat
	> hallo
	> l
	minishell: echo: Bad file descriptor


OPTIONAL
- EXPORT KEY+=value
- FD LIMIT
- EXIT_CODE inside struct bc errno can be changed by other functions