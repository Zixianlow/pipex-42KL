/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzi-xian <lzi-xian@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:05:59 by lzi-xian          #+#    #+#             */
/*   Updated: 2023/02/07 13:56:32 by lzi-xian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_err_n_exit(char *s, int i)
{
	perror(s);
	exit(i);
}

char	*ft_px_get_env_path(char **env)
{
	int	i;

	i = 0;
	while (*env)
	{
		if (!ft_strncmp("PATH=", *env, 5))
			return (*env + 5);
		env++;
	}
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac != 5)
		ft_err_n_exit("Invalid number of arguments.\n", 1);
	pipex.av = av;
	pipex.env = env;
	pipex.infile = open(av[1], O_RDONLY);
	if (pipex.infile == -1)
		ft_err_n_exit("Infile", 0);
	pipex.av = av;
	pipex.outfile = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex.outfile < 0)
		ft_err_n_exit("Outfile", 1);
	if (pipe(pipex.fd) < 0)
		ft_err_n_exit("Pipe", 0);
	pipex.env_paths_str = ft_px_get_env_path(env);
	pipex.env_paths_arr = ft_split(pipex.env_paths_str, ':');
	ft_fork_and_child(&pipex, av, env);
	close(pipex.infile);
	close(pipex.outfile);
	exit(0);
}
