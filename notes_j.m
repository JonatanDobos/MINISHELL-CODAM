TODO:

- INP[chmod 000 infile && <infile cat | cat >outfile] FREEZES!
- INP[<file] EXITS MINISHELL!
- MALLOC PROTECTION!
- SIGNALS!
- HEREDOC
- WAITPD protection if killsig in cat
- EXIT_CODE inside struct bc errno can be changed by other functions

OPTIONAL
- EXPORT KEY+=value
- FD LIMIT


HEREDOC:
- fix pipes
- fix unlimited loop when several heredocs