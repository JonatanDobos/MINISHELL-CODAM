>>	PIPEX
	system command uitvoeren zoals normaal in Pipex
	builtins uitvoeren met een functie zoals execve:
		envp en char **cmd ontvangen
		builtins uitvoeren vanuit functie, niet executable
		op basis van return van builtin functie een errno setten
		exit() wanneer succesvol

>>	SIGNALS
	geen idee